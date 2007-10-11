
#include "includes/main.h"

int cAddiere(lua_State* L);

int main()
{
   //luac_interface* lua;
   lua_State* L=lua_open();
   luaL_openlibs(L);
   lua_register(L,"addiere",cAddiere);
   luaL_dofile(L,"main.lua");
   CallLuaFunction(L,"add2",1,3,"100","250","70");
   int result = GetReturnValue(L);
   //int result = get_lua_iVar(L,"ergebnis");
   printf("Value of result is %d\n",result);
   lua_close(L);
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
int GetReturnValue(lua_State* lState)
{
    return GetReturnValue(lState,0);
}
int GetReturnValue(lua_State* lState, int index)
{
    int result = (int)lua_tonumber(lState,lua_gettop(lState)+index);
    return result;
}/*
int get_lua_iVar(lua_State* lState, char * myvar)
{
    lua_pushstring(lState, myvar);
    lua_gettable(lState,LUA_GLOBALSINDEX);
    int result = (int)lua_tonumber(lState,-1);
    return result;
}
*/
void CallLuaFunction(lua_State* lState, const char* fncName, int nResults, int nParams, ...)
{
    int i=0;
    char* myparam;
    lua_getglobal(lState, fncName);
    va_list args;
    va_start(args,nParams);
    while(i < nParams)
    {
        i++;
        myparam=va_arg(args,char*);
        printf("%d: %s\n",i,myparam);
        lua_pushstring(lState,myparam);
    }

    va_end(args);
    lua_pcall(lState,nParams,nResults,0);//i,nResults);
}


