#ifndef LUA_OBJ
#define LUA_OBJ
#include "stdafx.h"
#include "lua_Table.h"
#include "lua_engine.h"
class lua_obj
{
public:
   lua_Table* m_lptData;
   lua_obj_type* m_lpotType;
   lua_obj();
   lua_obj(lua_obj_type* m_lpotType);
   void AssignObjType(lua_obj_type* m_lpotType);
   void CheckType();
   const char* TableName();
   lua_Table* GetTable();
};
#endif
