// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDownPlayerPawn.h"

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
		const auto Vec = PlayerController->GetMoveVec() * MoveSpeed * DeltaTime;
		FVector NewLocation = GetActorLocation();
		NewLocation.X += Vec.X;
		NewLocation.Y += Vec.Y;
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void ATopDownPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

