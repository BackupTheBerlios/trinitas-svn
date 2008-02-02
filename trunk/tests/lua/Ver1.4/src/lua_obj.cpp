#include "lua_engine.h"

const char* lua_obj::GetTypeName(const char* sShort)
{
   int id = GetTypeId();
   g_lEngine->CallLuaMethod("language","get","s",sShort);
   lua_getfield(g_lState,-1,"items");
   lua_pushnumber(g_lState, id);
   lua_gettable(g_lState, -2);
   lua_getfield(g_lState,-1,"name");
   const char* sTypeName = lua_tostring(g_lState, -1);
   lua_pop(g_lState, 7);
   return sTypeName;
}
int lua_obj::GetTypeId()
{
   return g_lEngine->getobjectnumber(this,"type.ID");
}
