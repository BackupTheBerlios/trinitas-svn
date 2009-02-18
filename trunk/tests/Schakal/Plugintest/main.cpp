#include <iostream>
#include <windows.h>
#include "stdafx.h"
#include "lua_engine.h"


using namespace std;

int main()
{
    HINSTANCE__* libraryHandle = LoadLibrary("luaplugin.dll");
    if(libraryHandle)
      printf("Library exists!\n");
    typedef void* ( *getPlugFunc)(long);
    getPlugFunc getPlug;
    getPlug = (getPlugFunc) GetProcAddress(libraryHandle, "getPlugin");
    if(getPlug)
      printf("Plugin exists!\n");
    LuaPlugin* luaPlugin = (LuaPlugin*) getPlug(10);
    if(luaPlugin)
      printf("Plugin successfully implemented!\n");
    luaPlugin->Do();
    printf("Name: %d\n", luaPlugin->GetID());
    luaPlugin->Test();
    return 0;

}
