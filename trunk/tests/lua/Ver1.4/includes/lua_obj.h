#ifndef LUA_OBJ
#define LUA_OBJ
#include "stdafx.h"
class lua_obj
{
public:
   lua_Table* m_lptData;
   lua_obj_type* m_lpotType;
   lua_obj() {}
   lua_obj(lua_obj_type* m_lpotType);
   void AssignObjType(lua_obj_type* m_lpotType);
   const char* TableName();
};
#endif
