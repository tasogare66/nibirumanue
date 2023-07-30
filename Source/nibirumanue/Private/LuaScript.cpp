// Fill out your copyright notice in the Description page of Project Settings.
#include "LuaScript.h"

#include "lua.hpp"

namespace LuaScr {
    template <typename T>
    void FStringToBytes(const FString& String, T& OutBytes)
    {
        const int32 StringLength = String.Len();
        OutBytes.SetNum(StringLength);
        for (int32 i = 0; i < StringLength; ++i)
        {
            const auto CharValue = static_cast<uint16>(String[i]);
            if (CharValue == 0xffff)
            {
                OutBytes[i] = 0;
            }
            else
            {
                OutBytes[i] = static_cast<uint8>(String[i]);
            }
        }
    }
}

ULuaScript::ULuaScript()
{
}

ULuaScript::~ULuaScript()
{
    Destroy();
}

void ULuaScript::Initialize(const FStringView& InScrName)
{
    Destroy();
    mScriptsPath = FPaths::Combine(FPaths::ProjectContentDir(), TEXT("nibirumanue/Scripts/"));
    mLuaState = luaL_newstate();

    luaL_openlibs(mLuaState);

    // load "package" for allowing minimal setup
    luaL_requiref(mLuaState, "package", luaopen_package, 1);
    lua_pop(mLuaState, 1);

    TArray<uint8, TInlineAllocator<256>> PathBytes;
    LuaScr::FStringToBytes(mScriptsPath, PathBytes);
    lua_pushlstring(mLuaState, reinterpret_cast<char*>(PathBytes.GetData()), PathBytes.Num());
    lua_setglobal(mLuaState, "lua_path");

    // override print

    if (!InScrName.IsEmpty())
    {
        if (!RunFile(InScrName))
        {
            //if (bLogError) LogError(LastError);
            //ReceiveLuaError(LastError);
            //bDisabled = true;
            return;
        }
    }
}

void ULuaScript::Destroy()
{
    if (!mLuaState) return;
    lua_close(mLuaState);
    mLuaState = nullptr;
}

void ULuaScript::GetField(int Index, const char* FieldName) { lua_getfield(mLuaState, Index, FieldName); }


bool ULuaScript::RunFile(const FStringView& InScrName, int32 NRet)
{
    TArray<uint8> Code;
    FString AbsoluteFilename = FPaths::Combine(mScriptsPath, FString(InScrName)); //Scriptsディレクトリにluaファイルを配置
    if (!FPaths::FileExists(AbsoluteFilename))
    {
        //LastError = FString::Printf(TEXT("Unable to open file %s"), *Filename);
        //FLuaValue LuaLastError = FLuaValue(LastError);
        //FromLuaValue(LuaLastError);
        return false;
    }

    if (FFileHelper::LoadFileToArray(Code, *AbsoluteFilename))
    {
        if (RunCode(Code, AbsoluteFilename, NRet))
        {
            return true;
        }
        return false;
    }

    //LastError = FString::Printf(TEXT("Unable to open file %s"), *Filename);
    //FLuaValue LuaLastError = FLuaValue(LastError);
    //FromLuaValue(LuaLastError);
    return false;
}

bool ULuaScript::RunCode(const TArray<uint8>& Code, const FString& CodePath, int NRet)
{
    FString FullCodePath = FString("@") + CodePath;

    if (luaL_loadbuffer(mLuaState, (const char*)Code.GetData(), Code.Num(), TCHAR_TO_ANSI(*FullCodePath)))
    {
        LastError = FString::Printf(TEXT("Lua loading error: %s"), ANSI_TO_TCHAR(lua_tostring(mLuaState, -1)));
        return false;
    }
    else
    {
        if (lua_pcall(mLuaState, 0, NRet, 0))
        {
            LastError = FString::Printf(TEXT("Lua execution error: %s"), ANSI_TO_TCHAR(lua_tostring(mLuaState, -1)));
            return false;
        }
    }

    return true;
}
