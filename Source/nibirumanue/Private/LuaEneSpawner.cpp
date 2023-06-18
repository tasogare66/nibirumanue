// Fill out your copyright notice in the Description page of Project Settings.


#include "LuaEneSpawner.h"
#include "LuaBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#define KEY_GLOBAL_STRING_LUA_PATH "lua_path" // Lua パス
#define KEY_GLOBAL_FLOAT_ELAPSED_TIME "elapsed_time" // 経過時間
#define KEY_GLOBAL_FUNC_PRINT "print" // 文字列を出力
#define KEY_GLOBAL_FUNC_QUIT "quit" // 終了

UEneSpawnerLuaState::UEneSpawnerLuaState()
{
    LuaPath = FPaths::Combine(FPaths::ProjectContentDir(), TEXT("nibirumanue/Scripts/"));
    Table.Add(KEY_GLOBAL_STRING_LUA_PATH, ULuaBlueprintFunctionLibrary::LuaCreateString(LuaPath));
    Table.Add(KEY_GLOBAL_FLOAT_ELAPSED_TIME, ULuaBlueprintFunctionLibrary::LuaCreateNumber(0.0f));
    //Table.Add(KEY_GLOBAL_FUNC_PRINT, ULuaBlueprintFunctionLibrary::LuaCreateUFunction(UEneSpawnerLuaState::StaticClass(), (GET_FUNCTION_NAME_CHECKED(UEneSpawnerLuaState, Print)).ToString()));
    //Table.Add(KEY_GLOBAL_FUNC_QUIT, ULuaBlueprintFunctionLibrary::LuaCreateUFunction(UEneSpawnerLuaState::StaticClass(), (GET_FUNCTION_NAME_CHECKED(UEneSpawnerLuaState, Quit)).ToString()));
    //MEMO:StaticClass() は FuncTableに関数がなかった、これだと登録されていない
}

void UEneSpawnerLuaState::ReceiveLuaError_Implementation(const FString& error_text)
{
    FPlatformMisc::MessageBoxExt(EAppMsgType::Ok, *error_text, TEXT("Error"));
    Quit();
}

void UEneSpawnerLuaState::UpdateElapsedTime(float delta_seconds)
{
    FLuaValue lua_value = ULuaBlueprintFunctionLibrary::LuaGetGlobal(this, UEneSpawnerLuaState::StaticClass(), KEY_GLOBAL_FLOAT_ELAPSED_TIME);
    ULuaBlueprintFunctionLibrary::LuaSetGlobal(this, UEneSpawnerLuaState::StaticClass(), KEY_GLOBAL_FLOAT_ELAPSED_TIME, (lua_value.ToFloat() + delta_seconds));
}

void UEneSpawnerLuaState::Print(FLuaValue arg_text)
{
    GEngine->AddOnScreenDebugMessage(INDEX_NONE, FLT_MAX, FColor::Cyan, *(arg_text.ToString()));
}

void UEneSpawnerLuaState::Quit()
{
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}
