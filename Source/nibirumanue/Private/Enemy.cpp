// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "PlayerArms.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"

AEnemy::AEnemy()
{
    // collision向け
    Tags.AddUnique(TEXT("Enemy"));
}

void AEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!IsAlive())
    {
        if (UWorld* World = GetWorld())
        {
            SpawnDefeatedEffect();
            World->DestroyActor(this);
            return;
        }
    }

    UpdateEne(DeltaTime);
}

void AEnemy::SpawnDefeatedEffect()
{
    if (IsValid(DefeatedEffect) && DefeatedEffect->IsValid())
    {
        UNiagaraComponent* NewEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(),
            DefeatedEffect,
            GetActorLocation(),
            FRotator(0),
            FVector(1),
            true,
            true,
            ENCPoolMethod::AutoRelease,
            true);
    }
}


void AEneSnake::UpdateEne(float DeltaTime)
{
    if (const auto* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0))
    {
        const auto Location = GetActorLocation();
        auto Dir = PlayerPawn->GetActorLocation() - Location;
        Dir.Z = 0.0f;
        Dir.Normalize();
        const auto Len = 9.f * DeltaTime * 1.f; // GameSeq::inst().getDifV(1.f, 3.f);
        SetActorLocationAndRotation(Location + Dir * Len, FRotator(Dir.X < 0.f ? 180.f : 0.f, 0.f, 0.f), true);
    }
}
