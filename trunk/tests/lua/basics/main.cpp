extern "C"
{
   #include <lua.h>
   #include <lualib.h>
   #include <lauxlib.h>
}
#include <stdarg.h>
#include "main.h"

int cAddiere(lua_State* L);

int main()
{
   //luac_interface* lua;
   lua_State* L=lua_open();//=lua->State();
   //lua_State* L=lua_open();
   luaL_openlibs(L);
   lua_register(L,"addiere",cAddiere);
   luaL_dofile(L,"main.lua");
   int result = get_lua_iVar(L,"ergebnis");
   printf("Teste...C++ Funktion mit LUA aufrufen\n");
   printf("Ergebnis von cAddiere ist: %d\n",result);
   return 1;
}

int cAddiere(lua_State* L)
{
    double a,b;
    a = lua_tonumber(L, 1);
    b = lua_tonumber(L, 2);
    lua_pushnumber(L, a+b);
    return 1;
}

