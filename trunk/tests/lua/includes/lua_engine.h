

#ifndef LUA_ENGINE_H
#define LUA_ENGINE_H
#include <iostream>
#include <list.h>

#include "stdafx.h"
#include "lua_obj.h"
#include "lua_event.h"
#include "TrinitasPlugin.h"
#define g_lState lua_engine::m_lEngine->m_lState
#define g_lEngine lua_engine::m_lEngine


class lua_engine
{
public:
   lua_engine();
   ~lua_engine();

   static lua_engine* m_lEngine;
   lua_State* m_lState;
   list<lua_obj*> m_listlo;
   list<lua_obj*>::iterator m_listlo_i;
   list<lua_event*> m_listlev;
   list<lua_event*>::iterator m_listlev_i;

   clock_t m_curTime;

   void OpenLibrary(void (*fp)(lua_State*));
   void RegisterFunction(const char* sFunction, lua_CFunction fn);
   void SetPanicFunction(lua_CFunction panicf);
   lua_obj* lua_engine::RegisterObject();
   static int lib_RegisterObject(lua_State* L);

   void CallLuaMethod(const char* sLuaClass, const char* sMethod, char* format, ... );
   lua_obj* CreateCharacter(const char* sRace,const char* sLanguage);
   lua_obj* CreateItem(const char* sType);
   void CreateItemType(const char* sName);
   void Use(lua_obj* pUser, lua_obj* pSource, lua_obj* pTarget);

   // Obj->Stack Access Functions
   void*          getobjectpointer(lua_obj* loObj, const char* sVar);
   int            getobjectboolean(lua_obj* loObj, const char* sVar);
   int            getobjectnumber(lua_obj* loObj, const char* sVar);
   const char*    getobjectstring(lua_obj* loObj, const char* sVar);
   void           getluavar(const char* sVar);

   void pushuserdata(void* ud);
   int pushvarg(char* format, va_list* varg);
   void pushobject(lua_obj* loObj);
   va_list* tovarg(char* format, ...);
   int checkstack();

   void showvlist();


   // Language functions
   void GetLanguage(const char* sShort);
   void AddWords(const char* sVar, const char* sWords, const char* sShort);
   const char* GetWords(const char* sVar, const char* sShort);

   // Event functions
   void CheckEvents();
   lua_event* lua_engine::StartEvent(int difTime);
   //void StartEvent_UseWith(lua_obj* pUser, lua_obj* pSource, lua_obj* pTarget, int difTime);


   void ParseFile(const char* sFile);

   struct Debug
   {
   };



};



class lua_plugin : public TrinitasPlugin
{
public:
   lua_plugin();

   char* GetName();
   static lua_plugin* Get();

   void* Do();
   void Close();
   void Test();


private:
   static lua_plugin* m_lPlugin;
   static lua_engine* m_lEngine;
};




#endif

