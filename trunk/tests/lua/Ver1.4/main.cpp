
#include <string.h>
#include <time.h>
#include "includes/stdafx.h"
#include "includes/lua_engine.h"

using namespace std;

int main()
{

   lua_engine* luaEngine;
   luaEngine = new lua_engine();
   luaEngine->Start();

   // Parses necessary lua functions
   luaEngine->ParseFile("scripts/base_common.lua");

   luaEngine->CreateItemType("Hatchet",1001);
   luaEngine->CreateItemType("Tree",1002);
   luaEngine->CreateItemType("ChoppedTree",1003);
   lua_obj* david = luaEngine->CreateCharacter("human");
   lua_obj* lpoInventar[32];
   lpoInventar[0] = luaEngine->CreateItem("Hatchet");
   lpoInventar[1] = luaEngine->CreateItem("Tree");
   const char* sType1 = lpoInventar[1]->GetTypeName();
   luaEngine->Use(david, lpoInventar[0],lpoInventar[1]);
   const char* sType2 = lpoInventar[1]->GetTypeName();


   printf("Mein Baum war ein %s und ist nun ein %s\n",sType1,sType2);
   luaEngine->Release();
   return 1;
}
