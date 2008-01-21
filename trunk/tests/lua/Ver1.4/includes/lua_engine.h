#ifndef LUAENGINE
#define LUAENGINE
#include "singletons.h"
#define g_lState lua_engine::Get()->m_lState
#define g_lEngine lua_engine::Get()

class lua_engine : public TSingleton<lua_engine>
{
public:
   lua_State* m_lState;
   list<lua_script> m_listlscr;
   list<lua_script>::iterator m_listlscr_i;
   list<lua_obj_type*> m_listlpot;
   list<lua_obj_type*>::iterator m_listlpot_i;
   list<lua_event*> m_listlev;
   list<lua_event*>::iterator m_listlev_i;
   void RegisterCppFunction(const char* sFunction, lua_CFunction fn);
   void CallScript(lua_obj* loSource, lua_obj* loTarget);
   lua_obj_type* AddLuaObjType(const char* sName);
   lua_obj_type* GetLuaObjType(const char* sName);
   void AssignScript(const char* sFunction, lua_obj_type* lpotSource, lua_obj_type* lpotTarget);
   void AssignScript(const char* sFunction, const char* sSource, const char* sTarget);
   void Start();
   void Release();
   void ParseFile(const char* sFile);
};
#endif

