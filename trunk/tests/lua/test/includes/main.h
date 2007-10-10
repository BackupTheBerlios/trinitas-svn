extern "C"
{
   #include <lua.h>
   #include <lualib.h>
   #include <lauxlib.h>
}
#include <stdarg.h>
#include "luac_interface.h"


int get_int_var(lua_State *L, char * myvar);
void CallLuaFunction(lua_State* lState, const char* fncName, int nResults, char* param, ...);
int GetReturnValue(lua_State* lState, int index);


int get_lua_iVar(lua_State* lState, char * myvar)
{
    lua_pushstring(lState, myvar);
    lua_gettable(lState,LUA_GLOBALSINDEX);
    int result = (int)lua_tonumber(lState,-1);
    return result;
}
void CallLuaFunction(lua_State* lState, const char* fncName, int nResults, char* param, ...)
{
    int i;
    //lua_getfield(lState, LUA_GLOBALSINDEX, fncName);
    va_list args;
    va_start(args,param);
    while(param!=NULL)
    {
        i++;
        //lua_pushstring(lState,param);
        param = va_arg(args,char*);
    }
    va_end(args);
    lua_call(lState,2,1);//i,nResults);
}
