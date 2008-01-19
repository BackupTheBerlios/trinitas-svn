#include "stdafx.h"

int IsType(lua_State* lState)
{

}
int cAddiere(lua_State* L)
{
    double a,b;
    a = lua_tonumber(L, 1);
    b = lua_tonumber(L, 2);
    lua_pushnumber(L, a+b);
    return 1;
}
