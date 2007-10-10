
#include "includes/main.h"

int cAddiere(lua_State* L);

int main()
{
   //luac_interface* lua;
   lua_State* L=lua_open();//=lua->State();
   //lua_State* L=lua_open();
   //luaL_openlibs(L);
   lua_register(L,"addiere",cAddiere);
   luaL_dofile(L,"main.lua");
   CallLuaFunction(L,"add2",1,"200","150");
   //int result = GetReturnValue(L);
   //int result = get_lua_iVar(L,"ergebnis");
   //printf("Value of result is %d\n",result);
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
int GetReturnValue(lua_State* lState, int index = 0)
{
    int result = (int)lua_tonumber(lState,lua_gettop(lState)+index);
    return result;
}

