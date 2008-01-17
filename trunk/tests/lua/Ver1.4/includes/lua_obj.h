#ifndef LUA_OBJ
#define LUA_OBJ
#include "stdafx.h"
class lua_Obj
{
public:
   lua_Table* tTab;
   int id;
   lua_Obj()
   {
   }
   lua_Obj(int nId);
   void DoFile();
   void UseWith(lua_Obj* targObj);
   const char* TableName();
   void ScriptUpdate();
   void TableUpdate();
};
#endif
