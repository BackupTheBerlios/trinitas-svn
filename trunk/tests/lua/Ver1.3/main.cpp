
#include "includes/main.h"
#include <iostream>

int main()
{
   lua_State* L=lua_open();
   luaL_openlibs(L);
   lc_init(L);
   time_t start, finish;
   time(&start);
   luaL_dofile(L,"scripts/test.lua");
   time(&finish);
   printf("Time - Lua: %.5f seconds\n", difftime(finish,start)*100);
   time(&start);
   for(double i = 0; i < 1000000000; i++)
   {
   }
   time(&finish);
   printf("Time - Cpp: %.5f seconds\n", difftime(finish,start));
   /*
   lua_Obj* eineAxt = new lua_Obj(L,1001);
   lua_Obj* einBaum = new lua_Obj(L,1002);
   eineAxt->DoFile();
   eineAxt->UseWith(einBaum);
   printf("AxtID: %d\n",eineAxt->id);
   printf("BaumID: %d\n",einBaum->id);
   */
   lua_close(L);
   return 1;
}