// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuaState.h"
#include "LuaComponent.h"
#include "LuaEneSpawner.generated.h"

class AEneSpawner;

UCLASS()
class UEneSpawnerLuaState : public ULuaState
{
    GENERATED_BODY()

public:	
    UEneSpawnerLuaState();

    void ReceiveLuaError_Implementation(const FString& error_text); // Lua エラー受信（実装）
    void UpdateElapsedTime(float delta_seconds); // 経過時間を更新

    UFUNCTION()
    void Print(FLuaValue arg_text); // 文字列を出力

    UFUNCTION()
    void Quit();

    FString LuaPath;
};
