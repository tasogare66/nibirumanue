// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EneSpawner.generated.h"

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
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    void UpdateSpawn(float DeltaTime);

protected:
    void SpawnEne();
    void TestSpawn();

    UPROPERTY(BlueprintReadOnly, Category = "EneSpawner")
    int64 mEneCount = 0;

    UPROPERTY(BlueprintReadWrite, Category = "EneSpawner")
    int64 mEneCountMax = 1000;
};
