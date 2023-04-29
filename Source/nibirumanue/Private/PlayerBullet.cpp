// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBullet.h"

// Sets default values
APlayerBullet::APlayerBullet()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

void APlayerBullet::Setup(const FVector& InDir)
{
    mDir = InDir;
    mDir.Normalize();
}

// Called when the game starts or when spawned
void APlayerBullet::BeginPlay()
{
    Super::BeginPlay();

    SetLifeSpan(1.0f);
}

// Called every frame
void APlayerBullet::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    const auto MoveVec = mDir* mSpeed* DeltaTime;
    AddActorWorldOffset(MoveVec, true);
}
