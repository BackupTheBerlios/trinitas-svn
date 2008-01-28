#ifndef LUAENGINE
#define LUAENGINE
#include <iostream>
#include <list.h>
#include "singletons.h"
#include "stdafx.h"
#include "lua_obj_type.h"
#include "lua_obj.h"
#define g_lState lua_engine::Get()->m_lState
#define g_lEngine lua_engine::Get()

class lua_engine : public TSingleton<lua_engine>
{
public:
   lua_State* m_lState;
   list<lua_obj_type*> m_listlpot;
   list<lua_obj_type*>::iterator m_listlpot_i;
   list<lua_obj*> m_listlpo;
   list<lua_obj*>::iterator m_listlpo_i;
   //list<lua_event*> m_listlev;
   //list<lua_event*>::iterator m_listlev_i;
   void OpenLibrary(void (*fp)(lua_State*));
   void RegisterFunction(const char* sFunction, lua_CFunction fn);
   void SetPanicFunction(lua_CFunction panicf);

   lua_obj_type* AddLuaObjType(const char* sName);
   lua_obj_type* GetLuaObjType(const char* sName);
   lua_obj* lua_engine::CreateObject(const char* sName);
   lua_obj* lua_engine::CreateObject_meta(const char* sName, const char* mtName);
   lua_obj* lua_engine::CreateCharacter(const char* sName);
   lua_obj* lua_engine::CreateItem(const char* sName);
   // Lua calling functions
   void Use(lua_obj* loUser, lua_obj* loSource, lua_obj* loTarget);

   void Start();
   void Release();
   void ParseFile(const char* sFile);
};

void lua_pushuserdata(lua_State* L, void* ud);
int checkmystack(lua_State* L);


#endif

