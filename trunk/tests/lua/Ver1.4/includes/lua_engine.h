#ifndef LUAENGINE
#define LUAENGINE
#include <iostream>
#include <list.h>
#include "singletons.h"
#include "stdafx.h"
#include "lua_obj.h"
#define g_lState lua_engine::Get()->m_lState
#define g_lEngine lua_engine::Get()

class lua_engine : public TSingleton<lua_engine>
{
public:
   lua_State* m_lState;
   list<lua_obj*> m_listlo;
   list<lua_obj*>::iterator m_listlo_i;
   //list<lua_event*> m_listlev;
   //list<lua_event*>::iterator m_listlev_i;
   void OpenLibrary(void (*fp)(lua_State*));
   void RegisterFunction(const char* sFunction, lua_CFunction fn);
   void SetPanicFunction(lua_CFunction panicf);
   lua_obj* lua_engine::RegisterObject();

   void CallLuaMethod(const char* sLuaClass, const char* sMethod, char* format, ... );
   lua_obj* CreateCharacter(const char* sRace);
   lua_obj* CreateItem(const char* sType);
   void CreateItemType(const char* sName,int nId);
   void Use(lua_obj* pUser, lua_obj* pSource, lua_obj* pTarget);

   // Obj->Stack Access Functions
   void*          getobjectpointer(lua_obj* loObj, const char* sVar);
   int            getobjectboolean(lua_obj* loObj, const char* sVar);
   int            getobjectnumber(lua_obj* loObj, const char* sVar);
   const char*    getobjectstring(lua_obj* loObj, const char* sVar);
   void           getluavar(const char* sVar);


   void Start();
   void Release();
   void ParseFile(const char* sFile);
};

void lua_pushuserdata(lua_State* L, void* ud);
int checkmystack(lua_State* L);
int lib_RegisterObject(lua_State* L);
int lua_pushvarg(lua_State*L, char* format, va_list* varg);
void lua_pushobject(lua_State* L, lua_obj* loObj);


#endif

