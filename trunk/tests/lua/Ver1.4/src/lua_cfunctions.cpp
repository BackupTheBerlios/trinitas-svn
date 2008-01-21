#include "stdafx.h"
void CheckStack(int a)
{
   const char* b;
   b = lua_tostring(g_lState, a);
   printf("&%i: %s\n",a,b);
}
int lua_CCheckStack(lua_State* L)
{
    int a;
    const char* b;
    a = lua_tonumber(L, 1);
    b = lua_tostring(L, a);
    printf("&%i: %s\n",a, b);
    return 1;
}
