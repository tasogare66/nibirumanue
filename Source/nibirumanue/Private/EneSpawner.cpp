// Fill out your copyright notice in the Description page of Project Settings.


#include "EneSpawner.h"

#include "Enemy.h"
#include "GameUtil.h"

// Sets default values
AEneSpawner::AEneSpawner()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEneSpawner::BeginPlay()
{
    Super::BeginPlay();

    // Luaステート,singletonみたい
    //mLuaState = Cast<UEneSpawnerLuaState>(FLuaMachineModule::Get().GetLuaState(UEneSpawnerLuaState::StaticClass(), GetWorld()));

    //const FString ScriptPath = FPaths::Combine(mLuaState->LuaPath, TEXT("level0.lua"));
    //const auto Ret = ULuaBlueprintFunctionLibrary::LuaRunNonContentFile(this, mLuaState->StaticClass(), ScriptPath, false); // スクリプトをロード＆実行
    //ensure(!Ret.IsNil());
}

void AEneSpawner::UpdateSpawn(float DeltaTime)
{
    //if (!bEndFlag && IsValid(mLuaState))
    //{
    //    mLuaState->UpdateElapsedTime(DeltaTime);

    //    //FIXME:やり方わからない,GetInternalLuaState で直接呼び出し
    //    auto thread = mThread.LuaState->GetInternalLuaState();
    //    int status = lua_resume(mLuaState->GetInternalLuaState(), thread, 0);
    //    switch (status) {
    //    case LUA_OK:
    //    case LUA_YIELD:
    //        break;
    //    default:
    //        {
    //            auto tmp =lua_tostring(thread, -1);
    //            bEndFlag = true;
    //            ensure(false);
    //        }
    //        break;
    //    }

    //    if (auto ret = mThread.LuaState->ToInteger(-1)) {
    //        // 終了
    //        bEndFlag = true;
    //    }
    //}

    TestSpawn();
}

void AEneSpawner::SpawnEne()
{
    //FIXME:アセットの参照方法   
    FName Path = TEXT("/Game/nibirumanue/Blueprints/BP_EneSnake.BP_EneSnake_C");
    TSubclassOf<AActor> ActorClass = TSoftClassPtr<AActor>(FSoftObjectPath(Path)).LoadSynchronous();
    if (ensure(ActorClass))
    {
        FVector SpawnLocation = UGameUtil::RandomCircle(0.0f, 170.0f);
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        auto* Actor = GetWorld()->SpawnActor<AEneSnake>(ActorClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);

        ++mEneCount;
    }
}

void AEneSpawner::TestSpawn()
{
    if (mEneCount > mEneCountMax) return;
    SpawnEne();
}
