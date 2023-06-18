// Fill out your copyright notice in the Description page of Project Settings.


#include "EneSpawner.h"

#include "Enemy.h"
#include "GameUtil.h"
#include "LuaEneSpawner.h"
#include "LuaMachine.h"
#include "LuaBlueprintFunctionLibrary.h"

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
    mLuaState = Cast<UEneSpawnerLuaState>(FLuaMachineModule::Get().GetLuaState(UEneSpawnerLuaState::StaticClass(), GetWorld()));

    const FString ScriptPath = FPaths::Combine(mLuaState->LuaPath, TEXT("level0.lua"));
    const auto Ret = ULuaBlueprintFunctionLibrary::LuaRunNonContentFile(this, mLuaState->StaticClass(), ScriptPath, false); // スクリプトをロード＆実行
    ensure(!Ret.IsNil());
    ResetThread();
}

void AEneSpawner::ResetThread()
{
    if (IsValid(mLuaState))
    {
        mThread = mLuaState->CreateLuaThread(FLuaValue());
        mThread.LuaState->GetGlobal("spawn_exec"); //実行する関数
    }
    else
    {
        ensure(false);
    }
}

void AEneSpawner::UpdateSpawn(float DeltaTime)
{
    if (IsValid(mLuaState))
    {
        mLuaState->UpdateElapsedTime(DeltaTime);

        //FIXME:やり方わからない,GetInternalLuaState で直接呼び出し
        auto thread = mThread.LuaState->GetInternalLuaState();
        lua_resume(mLuaState->GetInternalLuaState(), thread, 0);
    }

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
