#include <iostream>
#include <windows.h>
#include "stdafx.h"
#include "lua_engine.h"

using namespace std;

int main()
{
    HINSTANCE__* libraryHandle = LoadLibrary("console.dll");
    if(libraryHandle)
      printf("Library exists!\n");
    typedef lua_plugin* ( *getPlugFunc)(void);
    getPlugFunc getPlug;
    getPlug = (getPlugFunc) GetProcAddress(libraryHandle, "getPlugin");
    if(getPlug)
      printf("Plugin exists!\n");
    lua_plugin* luaPlugin = (lua_plugin*) getPlug();
    if(luaPlugin)
      printf("Plugin successfully implemented!\n");
    printf("Name: %s\n", luaPlugin->GetName());
    //printf("Test plugin:\n");
    //luaPlugin->Test();
    return 0;

}
