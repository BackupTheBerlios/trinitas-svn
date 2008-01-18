
#include "includes/stdafx.h"

int main()
{
   ctVar<const char*> myVar;
   myVar.Set("Hallo!");
   printf("%s\n",myVar.Get());
   lua_engine* luaEngine = new lua_engine();
   luaEngine->Start();
   lua_obj_type lotBaum = luaEngine->AddLuaObjType("Baum");
   lua_obj_type lotAxt = luaEngine->AddLuaObjType("Axt");
   luaEngine->ParseFile("scripts/main.lua");
   //lua_Obj* eineAxt = new lua_Obj(1001);
   //lua_Obj* einBaum = new lua_Obj(1002);
   /*eineAxt->DoFile();
   eineAxt->UseWith(einBaum);*/
   /*printf("AxtID: %d\n",eineAxt->id);
   printf("BaumID: %d\n",einBaum->id);*/
   luaEngine->Release();
   return 1;
}
