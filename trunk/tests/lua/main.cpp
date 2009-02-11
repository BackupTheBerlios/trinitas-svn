#include "includes/stdafx.h"
#include "includes/lua_engine.h"

extern "C" __declspec(dllexport) void* getPlugin(void)
{
   return (void*) new lua_plugin;
}

void lua_plugin::Test()
{
   m_lEngine->ParseFile("scripts/base_common.lua");

   lua_obj* david = m_lEngine->CreateCharacter("human","de");
   lua_obj* lpoInventar[32];
   lpoInventar[0] = m_lEngine->CreateItem("Hatchet");
   lpoInventar[1] = m_lEngine->CreateItem("Tree");
   printf("Start Event...\n");
   lua_event::usewith::Init(david, lpoInventar[0],lpoInventar[1],1500);

   while(strcmp(lpoInventar[1]->GetTypeName("de"),"extrem gefällter Baum")!=0)
   {
      m_lEngine->CheckEvents();
   }
   printf("Ready\n");
}
