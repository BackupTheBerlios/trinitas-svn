
#include <string.h>
#include <time.h>
#include "includes/stdafx.h"
#include "includes/lua_engine.h"
#include "includes/lua_cfunctions.h"

using namespace std;

int main()
{

   __time_64_t mytime;
   time_t mytime2;
   gmtime(&mytime);
   // Initializes the lua engine
   lua_engine* luaEngine;
   luaEngine = new lua_engine();
   luaEngine->Start();
   gmtime(&mytime2);
   printf("%d\n",difftime((time_t)mytime,(time_t)mytime2));

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
