// Fill out your copyright notice in the Description page of Project Settings.

#include "RngEngineSubsystem.h"

#include <chrono>
#include "Xoshiro.hpp"
#include "GenericPlatform/GenericPlatformProcess.h"

namespace Rng {
    class Random {
    public:
        Random() {
            auto s = std::time(nullptr);
            Xoshiro::Xoshiro256StarStar rng{ static_cast<uint64_t>(s) };
            {
                auto genSeed = [](uint64_t v) {
                    return Xoshiro::SplitMix64(v)();
                };
                auto state = rng.serialize();
                auto tp = std::chrono::steady_clock::now();
                uint64_t v = std::chrono::duration_cast<std::chrono::nanoseconds>(tp.time_since_epoch()).count();
                state[0] = genSeed(v);
                state[1] = genSeed(FPlatformProcess::GetCurrentProcessId());
                rng.deserialize(state);
            }
            for (auto& r : m_rngs) {
                r = Xoshiro::Xoshiro256StarStar{ rng() };
            }
        }
        ~Random() = default;
        auto& rng(Type t) { return m_rngs[static_cast<size_t>(t)]; }

        //[0.0-1.0)
        double rand(Type t) {
            //FW_ASSERT(m_assertion_cnt == 0);
            return Xoshiro::DoubleFromBits(this->rng(t)());
        }

        //[0.0-range)
        float randf(float range, Type t) {
            double d = this->rand(t);
            auto ret = d * static_cast<double>(range);
            return static_cast<float>(ret);
        }

        //[min-max)
        float rangef(float min, float max, Type t) {
            return this->randf(max - min, t) + min;
        }

        //[0-max]
        int32_t rand_int(int32_t max, Type t) {
            //FW_ASSERT(max >= 0);
            double d = this->rand(t);
            uint64_t u = max + 1;
            return static_cast<int32_t>(d * u);
        }

        //[min-max]
        int32_t range_int(int32_t min, int32_t max, Type t) {
            //FW_ASSERT(max - min >= 0);
            double d = this->rand(t);
            uint64_t u = max - min + 1;
            return static_cast<int32_t>(d * u) + min;
        }

        auto serialize(Type t) {
            return this->rng(t).serialize();
        }

        void deserialize(Type t, const State& state) {
            this->rng(t).deserialize(state);
        }

        void inc_assertion_cnt() { ++m_assertion_cnt; }
        void dec_assertion_cnt() { --m_assertion_cnt; }

    private:
        std::array<Xoshiro::Xoshiro256StarStar, static_cast<size_t>(Type::MAX)> m_rngs;
        uint32_t m_assertion_cnt = 0;
    } g_random;

    float randf(Type t) { return static_cast<float>(g_random.rand(t)); }
    float randf(float range, Type t) { return g_random.randf(range, t); }
    float range(float min, float max, Type t) { return g_random.rangef(min, max, t); }
    int32_t rand_int(int32_t max, Type t) { return g_random.rand_int(max, t); }
    int32_t range_int(int32_t min, int32_t max, Type t) { return g_random.range_int(min, max, t); }
    bool rand_bool(Type t) { return (rand_int(1, t) == 0); }
    State serialize(Type t) { return g_random.serialize(t); }
    void deserialize(Type t, const State& state) { g_random.deserialize(t, state); }
    uint64_t gen_splitmix(uint64_t seed) { return Xoshiro::SplitMix64(seed)(); } //指定seedのSplitMix64を生成
    int32_t SplitMix::range_int(int32_t min, int32_t max) {
        ensure(max - min >= 0);
        double d = Xoshiro::DoubleFromBits<uint64_t>((*this)());
        uint64_t u = max - min + 1;
        return static_cast<int32_t>(d * u) + min;
    }
}

// EngineSubSystemで初期化する
void URngEngineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    Rng::g_random = Rng::Random();
}

void URngEngineSubsystem::Deinitialize()
{
    Super::Deinitialize();
}
