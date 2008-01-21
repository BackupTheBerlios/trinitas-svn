
#include "includes/stdafx.h"
#include <string>

using namespace std;

int main()
{
   lua_engine* luaEngine;
   luaEngine = new lua_engine();
   luaEngine->Start();
   lua_obj_type* lpotTree = luaEngine->AddLuaObjType("Tree");
   lua_obj_type* lpotChoppedTree = luaEngine->AddLuaObjType("Chopped Tree");
   lua_obj_type* lpotHatchet = luaEngine->AddLuaObjType("Hatchet");
   luaEngine->ParseFile("scripts/main.lua");
   luaEngine->AssignScript("UseHatchetWithTree",lpotHatchet,lpotTree);
   lua_obj* meineAxt = new lua_obj(lpotHatchet);
   lua_obj* meinBaum = new lua_obj(lpotTree);
   luaEngine->CallScript(meineAxt,meinBaum);
   printf("Mein Baum ist nun ein %s\n",meinBaum->m_lpotType->m_sName);
   luaEngine->RegisterCppFunction("CheckStack", lua_CCheckStack);
   //lua_obj* eineAxt = new lua_obj(&lotBaum);
   //lua_Obj* einBaum = new lua_Obj(1002);
   /*eineAxt->DoFile();
   eineAxt->UseWith(einBaum);*/
   /*printf("AxtID: %d\n",eineAxt->id);
   printf("BaumID: %d\n",einBaum->id);*/
   //luaEngine->Release();
   return 1;
}
