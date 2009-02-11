


#ifndef LUA_OBJ_H
#define LUA_OBJ_H
#include "lua_engine.h"



class lua_obj
{
public:
   //int key2;
   int key;
   lua_State* L;
   const char* GetTypeName(const char* sShort);
   int GetTypeId();
};



#endif

