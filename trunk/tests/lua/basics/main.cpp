extern "C"
{
   #include <lua.h>
   #include <lualib.h>
   #include <lauxlib.h>
}

#include "main.h"

int main()
{
   luac_interface* lua;
   lua_State* L=lua->State();
   //lua_State* L=lua_open();
   //luaL_openlibs(L);
   luaL_dofile(L,"main.lua");
   //int result = get_lua_iVar(L,"result");
   //printf("Value of result is %d\n",result);
   return 1;
}


