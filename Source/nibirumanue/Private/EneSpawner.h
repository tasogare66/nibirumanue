// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LuaState.h"
#include "EneSpawner.generated.h"

class UEneSpawnerLuaState;
class UEneSpawnerLuaComponent;

UCLASS()
class AEneSpawner : public AActor
{
    GENERATED_BODY()
    
public:	
    // Sets default values for this actor's properties
    AEneSpawner();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:	
    void ResetThread();
    void UpdateSpawn(float DeltaTime); //更新処理,ATopDownGameState::Tickで更新される

protected:
    void SpawnEne();
    void TestSpawn();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EneSpawner")
    int64 mEneCount = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EneSpawner")
    int64 mEneCountMax = 1000;

    UPROPERTY()
    UEneSpawnerLuaState* mLuaState = nullptr;
    UPROPERTY()
    FLuaValue mThread;

    bool bEndFlag = false;
};
