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
    
}

// Called every frame
void AEneSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AEneSpawner::UpdateSpawn(float DeltaTime)
{
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
