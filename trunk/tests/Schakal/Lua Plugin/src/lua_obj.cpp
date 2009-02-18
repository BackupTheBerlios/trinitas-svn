
/*
 * Copyright 2007 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 *
 * @autor    David Jablonski, davidjablonski@web.de
 * @date     14.02.2009
 */


#include "lua_engine.h"


const char* LuaObj::GetTypeName(const char* sShort)
{
   int id = GetTypeId();
   glPlugin->CallLuaMethod("language","get","s",sShort);
   lua_getfield(glState,-1,"items");
   lua_pushnumber(glState, id);
   lua_gettable(glState, -2);
   lua_getfield(glState,-1,"name");
   const char* sTypeName = lua_tostring(glState, -1);
   lua_pop(glState, 4);
   return sTypeName;
}
int LuaObj::GetTypeId()
{
   return glPlugin->GetObjectNumber(this,"type.ID");
}
