#ifndef LUA_OBJ
#define LUA_OBJ
#include "stdafx.h"

class lua_obj
{
public:
   //int key2;
   int key;

   const char* GetTypeName(const char* sShort);
   int GetTypeId();
};
#endif
