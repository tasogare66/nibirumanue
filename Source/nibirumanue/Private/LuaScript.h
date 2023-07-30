// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LuaScript.generated.h"

struct lua_State;

/**
 * 
 */
UCLASS()
class ULuaScript : public UObject
{
    GENERATED_BODY()

public:
    ULuaScript();
    virtual ~ULuaScript();

    void Initialize(const FStringView& InScrName);
    void Destroy();

    void GetField(int Index, const char* FieldName);

    bool RunFile(const FStringView& InScrName, int32 NRet = 0);
    bool RunCode(const TArray<uint8>& Code, const FString& CodePath, int NRet);

    FString LastError;

protected:
    FString mScriptsPath;
    lua_State* mLuaState = nullptr;
};
