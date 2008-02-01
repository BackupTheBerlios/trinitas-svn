#include "lua_engine.h"

const char* lua_obj::GetTypeName()
{
   return g_lEngine->getobjectstring(this,"type.name");
}
int lua_obj::GetTypeId()
{
   return g_lEngine->getobjectnumber(this,"type.id");
}
