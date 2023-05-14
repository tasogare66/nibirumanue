// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDownGameState.h"

#include "EneSpawner.h"

ATopDownGameState::ATopDownGameState()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ATopDownGameState::BeginPlay()
{
    Super::BeginPlay();

    //FIXME:アセットの参照方法   
    FName Path = TEXT("/Game/nibirumanue/Blueprints/BP_EneSpawner.BP_EneSpawner_C");
    TSubclassOf<AActor> ActorClass = TSoftClassPtr<AActor>(FSoftObjectPath(Path)).LoadSynchronous();
    if (ensure(ActorClass))
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        mEneSpawner = GetWorld()->SpawnActor<AEneSpawner>(ActorClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
    }
    ensure(mEneSpawner);
}

// Called every frame
void ATopDownGameState::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    mEneSpawner->UpdateSpawn(DeltaTime);
}
