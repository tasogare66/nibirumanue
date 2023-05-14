// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameUtil.generated.h"

/**
 * 
 */
UCLASS()
class UGameUtil : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "GameUtil")
    static FVector RandomCircle(float StartRadius, float EndRadius);
};
