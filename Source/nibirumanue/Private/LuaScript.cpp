// Fill out your copyright notice in the Description page of Project Settings.
#include "LuaScript.h"

#include "lua.hpp"

void ULuaScript::test()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
}
