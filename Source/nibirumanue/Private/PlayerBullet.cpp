// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerBullet.h"

#include "Enemy.h"

// Sets default values
APlayerBullet::APlayerBullet()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    // collision向け
    OnActorBeginOverlap.AddDynamic(this, &APlayerBullet::OnBeginOverlap);
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

    if (mFlag.ToBeDestroyed)
    {
        if (UWorld* World = GetWorld())
        {
            World->DestroyActor(this);
        }
    }
}

void APlayerBullet::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    if (!IsAlive()) return;

    if (OtherActor->ActorHasTag(TEXT("Enemy")))
    {
        // 敵にダメージを与える
        auto* Enemy = Cast<AEnemy>(OtherActor);
        if (!IsValid(Enemy)) return;
        if (!Enemy->IsAlive()) return;

        const auto GiveDmg = GetPower();
        const auto GivenDmg = Enemy->GetHealth();
        Enemy->SubHealth(GiveDmg);
        this->SubHealth(GivenDmg);

        if (!IsAlive())
        {
            mFlag.ToBeDestroyed = true;
        }
    }
}
