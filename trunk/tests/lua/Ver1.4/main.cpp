
#include "includes/stdafx.h"


int main()
{
   printf("size of Hallo: %i\n",sizeofchar("Hallo"));
   lua_engine* luaEngine;
   luaEngine = new lua_engine();
   luaEngine->Start();
   lua_obj_type* lpotTree = luaEngine->AddLuaObjType("Tree");
   lua_obj_type* lpotChoppedTree = luaEngine->AddLuaObjType("Chopped Tree");
   lua_obj_type* lpotHatchet = luaEngine->AddLuaObjType("Hatchet");
   printf("Chopped tree is %i\n",luaEngine->GetLuaObjType("Chopped Tree"));
   luaEngine->ParseFile("scripts/main.lua");
   luaEngine->AssignScript("UseHatchetWithTree",lpotHatchet,lpotTree);
   lua_obj* meineAxt = new lua_obj(lpotHatchet);
   lua_obj* meinBaum = new lua_obj(lpotTree);
   luaEngine->CallScript(meineAxt,meinBaum);
   printf("Mein Baum ist nun ein %i\n",meinBaum->m_lpotType);
   //lua_obj* eineAxt = new lua_obj(&lotBaum);
   //lua_Obj* einBaum = new lua_Obj(1002);
   /*eineAxt->DoFile();
   eineAxt->UseWith(einBaum);*/
   /*printf("AxtID: %d\n",eineAxt->id);
   printf("BaumID: %d\n",einBaum->id);*/
   //luaEngine->Release();
   return 1;
}
int sizeofchar(const char* String)
{
   char TestString[255];
   sprintf(TestString,"%s",String);
   for (int i=0;i<255;i++)
   {
      printf("%i ",TestString[i]);
      if (TestString[i]==0)
      {
         printf("\n");
         return i;
      }
   }
}
