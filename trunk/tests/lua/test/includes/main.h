extern "C"
{
   #include <lua.h>
   #include <lualib.h>
   #include <lauxlib.h>
}
#include <stdarg.h>
#include "includes\luac_interface.h"


//int get_int_var(lua_State *L, char * myvar);
void CallLuaFunction(lua_State* lState, const char* fncName, int nResults, int nParams, ...);
//void CallLuaFunction(lua_State* lState);
int GetReturnValue(lua_State* lState);
int GetReturnValue(lua_State* lState, int index);

