
/*
 * Copyright 2007 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 *
 * @autor    David Jablonski, davidjablonski@web.de
 * @date     14.02.2009
 */


#include "lua_engine.h"


#ifndef BUILD_DLL
int main(void)
{
    printf("%s\n",TEXTS);
    LuaPlugin myPlug;
    myPlug.Do();
    myPlug.Test();
    return 0;
}
#else
bool WINAPI DllMain (HINSTANCE hInst     /* Library instance handle. */ ,
                       DWORD reason        /* Reason this function is being called. */ ,
                       LPVOID reserved     /* Not used. */ )
{
    return TRUE;
}
#endif

extern "C" DLLEXPORT void* getPlugin(long ID)
{
    LuaPlugin* luaPlugin = new LuaPlugin(ID);// = new LuaPlugin;
    //luaPlugin->mID = ID;
    return (void*) luaPlugin;
}

void LuaPlugin::Test()
{
    ParseFile("scripts/base_common.lua");

    LuaObj* david = CreateCharacter("human","de");
    LuaObj* lpoInventar[32];
    lpoInventar[0] = CreateItem("Hatchet");
    lpoInventar[1] = CreateItem("Tree");
    printf("Start Event...\n");
    LuaEvent::usewith::Init(david, lpoInventar[0],lpoInventar[1],1500);

    while(strcmp(lpoInventar[1]->GetTypeName("de"),"extrem gefällter Baum")!=0)
    {
        CheckEvents();
    }
    printf("Ready\n");
}
