// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EneSpawner.h"
#include "Templates/UniquePtr.h"
#include "GameFramework/GameStateBase.h"
#include "TopDownGameState.generated.h"

class AEneSpawner;

/**
 * 
 */
UCLASS()
class ATopDownGameState : public AGameStateBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:
	ATopDownGameState();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY()
	AEneSpawner* mEneSpawner = nullptr;
};
