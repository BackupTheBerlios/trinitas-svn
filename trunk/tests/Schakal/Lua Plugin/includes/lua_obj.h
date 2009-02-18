
/*
 * Copyright 2007 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 *
 * @date     14.02.2009
 */





#ifndef LUA_OBJ_H
#define LUA_OBJ_H

#include "lua_engine.h"



class LuaObj
{
public:
   //int key2;
   int mKey;
   const char* GetTypeName(const char* sShort);
   int GetTypeId();
};



#endif

