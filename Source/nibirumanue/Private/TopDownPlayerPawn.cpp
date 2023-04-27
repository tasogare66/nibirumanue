// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDownPlayerPawn.h"

#include "PlayerBullet.h"
#include "TopDownPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATopDownPlayerPawn::ATopDownPlayerPawn()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATopDownPlayerPawn::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void ATopDownPlayerPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    const auto* PlayerController = Cast<ATopDownPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    if (ensure(PlayerController))
    {
        //shoot
        const auto ShootVec = PlayerController->GetShootVec();
        if (ShootVec.Size() > 0.5f)
        {
            Shoot();
        }

        //move
        const auto MoveVec = PlayerController->GetMoveVec() * MoveSpeed * DeltaTime;
        FVector NewLocation = GetActorLocation();
        NewLocation.X += MoveVec.X;
        NewLocation.Y += MoveVec.Y;
        SetActorLocation(NewLocation);
    }
}

// Called to bind functionality to input
void ATopDownPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATopDownPlayerPawn::Shoot()
{
    if (auto* World = GetWorld())
    {
        //FIXME:アセットの参照方法   
        FName Path = TEXT("/Game/nibirumanue/Blueprints/BP_PlayerBullet.BP_PlayerBullet_C");
        TSubclassOf<AActor> ActorClass = TSoftClassPtr<AActor>(FSoftObjectPath(Path)).LoadSynchronous();
        if (ensure(ActorClass))
        {
            const FVector& SpawnLocation = GetActorLocation();
            const FRotator& SpawnRotator = GetActorRotation();
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            AActor* Actor = GetWorld()->SpawnActor<AActor>(ActorClass, SpawnLocation, SpawnRotator, SpawnParams);
        }
    }
}
