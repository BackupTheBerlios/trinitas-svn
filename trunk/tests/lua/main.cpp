#include "includes/stdafx.h"
#include "includes/lua_engine.h"


int main()
{

   lua_engine* luaEngine;
   luaEngine = new lua_engine();
   luaEngine->Start();
   luaEngine->ParseFile("scripts/base_common.lua");

   lua_obj* david = luaEngine->CreateCharacter("human","de");
   lua_obj* lpoInventar[32];
   lpoInventar[0] = luaEngine->CreateItem("Hatchet");
   lpoInventar[1] = luaEngine->CreateItem("Tree");
   printf("Start Event...\n");
   luaEngine->StartEvent_UseWith(david, lpoInventar[0],lpoInventar[1],500);

   while(strcmp(lpoInventar[1]->GetTypeName("de"),"extrem gefällter Baum")!=0)
   {
      luaEngine->CheckEvents();
   }
   printf("Ready\n");
   luaEngine->Release();
   return 1;
}
