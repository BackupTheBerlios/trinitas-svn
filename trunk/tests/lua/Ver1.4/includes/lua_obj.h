#ifndef LUA_OBJ
#define LUA_OBJ
#include "stdafx.h"
#include "lua_engine.h"

class lua_obj
{
public:
   //int key2;
   int key;

   const char* GetTypeName();
   int GetTypeId();
};
#endif
