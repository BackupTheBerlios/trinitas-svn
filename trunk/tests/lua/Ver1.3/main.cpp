
#include "includes/main.h"
#include <iostream>

int main()
{
   lua_State* L=lua_open();
   luaL_openlibs(L);
   lc_init(L);
   lua_Obj* eineAxt = new lua_Obj(L,1001);
   lua_Obj* einBaum = new lua_Obj(L,1002);
   eineAxt->DoFile();
   eineAxt->UseWith(einBaum);
   printf("AxtID: %d\n",eineAxt->id);
   printf("BaumID: %d\n",einBaum->id);
   lua_close(L);
   return 1;
}