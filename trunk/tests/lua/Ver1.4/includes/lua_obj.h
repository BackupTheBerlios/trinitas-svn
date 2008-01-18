#ifndef LUA_OBJ
#define LUA_OBJ
#include "stdafx.h"
class lua_Obj
{
public:
   lua_Table* tTab;
   lua_obj_type* lType;
   void DoFile();
   void UseWith(lua_Obj* targObj);
   const char* TableName();
   void ScriptUpdate();
   void TableUpdate();
};
#endif
