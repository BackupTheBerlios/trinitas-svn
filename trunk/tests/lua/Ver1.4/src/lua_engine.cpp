#include "stdafx.h"

void lua_engine::Start()
{
   lState=lua_open();
   luaL_openlibs(lState);
}
void lua_engine::Release()
{
   lua_close(lState);
   lState = NULL;
}
void lua_engine::ParseFile(const char* sName)
{
   luaL_dofile(lState,sName);
}
