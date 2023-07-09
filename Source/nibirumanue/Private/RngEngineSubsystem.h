// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "RngEngineSubsystem.generated.h"

namespace Rng {
    enum class Type {
        GAME,
        EFFECT,
        ETC,
        MAX
    };
    using State = std::array<uint64_t, 4>;
    float randf(Type t = Type::GAME);
    float randf(float range, Type t = Type::GAME);
    float range(float min, float max, Type t = Type::GAME);
    int32_t rand_int(int32_t max, Type t = Type::GAME);
    int32_t range_int(int32_t min, int32_t max, Type t = Type::GAME);
    bool rand_bool(Type t = Type::GAME);
    State serialize(Type t);
    void deserialize(Type t, State state);

    ////指定seedのSplitMix64を生成
    class SplitMix {
    public:
        SplitMix(const uint64_t seed)
            : m_state(seed)
        {}
        constexpr uint64_t operator()() {
            std::uint64_t z = (m_state += 0x9e3779b97f4a7c15);
            z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
            z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
            return z ^ (z >> 31);
        }
        int32_t range_int(int32_t min, int32_t max);
    private:
        uint64_t m_state;
    };
} //Rng

/**
 * 
 */
UCLASS()
class URngEngineSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
};
