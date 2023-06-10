// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerArms.generated.h"

UCLASS()
class APlayerArms : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerArms();

	float GetPower() const { return mPower * mHealth / mHealthMax; }
	void SubHealth(float v) { mHealth = FMath::Max(mHealth - v, 0.0f); }
	bool IsAlive() const { return (mHealth > 0.0f); }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	float mPower = 1.0f;
	float mHealth = 1.0f;
	float mHealthMax = 1.0f;
};
