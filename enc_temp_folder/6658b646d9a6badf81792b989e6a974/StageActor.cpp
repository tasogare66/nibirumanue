// Fill out your copyright notice in the Description page of Project Settings.

#include "StageActor.h"

#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"

// Sets default values
AStageActor::AStageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//for debug
	UKismetSystemLibrary::DrawDebugCircle(GetWorld(), FVector::ZeroVector, 100.0f, 12, FLinearColor::White, 0.0f, 1.0f);
}

