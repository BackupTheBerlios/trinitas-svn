
#include <string>
#include "includes/stdafx.h"
#include "lua_engine.h"
#include "lua_cfunctions.h"

using namespace std;

int main()
{


   // Initializes the lua engine
   lua_engine* luaEngine;
   luaEngine = new lua_engine();
   luaEngine->Start();
   luaEngine->OpenLibrary(lualib_character);
   luaEngine->OpenLibrary(lualib_item);
   // Adds some object types
   luaEngine->AddLuaObjType("Tree");
   luaEngine->AddLuaObjType("Chopped Tree");
   luaEngine->AddLuaObjType("Hatchet");
   luaEngine->AddLuaObjType("human");
   // Parses necessary lua functions
   luaEngine->ParseFile("scripts/main.lua");
   lua_obj* david = luaEngine->CreateCharacter("human");
   lua_obj* lpoInventar[32];
   lpoInventar[0] = luaEngine->CreateItem("Hatchet");
   lpoInventar[1] = luaEngine->CreateItem("Tree");
   luaEngine->Use(david, lpoInventar[0],lpoInventar[1]);
   printf("Mein Baum ist nun ein %s\n",lpoInventar[1]->m_lpotType->m_sName);
   luaEngine->Release();
   return 1;
}
