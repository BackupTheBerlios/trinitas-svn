#include "stdafx.h"

void lua_engine::Start()
{
   m_lState=lua_open();
   luaL_openlibs(m_lState);

}
void lua_engine::Release()
{
   lua_close(m_lState);
   m_lState = NULL;
   m_listlot.clear();
   m_listlscr.clear();
}
void lua_engine::ParseFile(const char* sFile)
{
   luaL_dofile(m_lState,sFile);
}
lua_obj_type lua_engine::AddLuaObjType(const char* sName)
{
   lua_obj_type lObjType;
   lObjType.sName = sName;
   m_listlot.push_back(lObjType);
   return lObjType;
}
lua_obj_type lua_engine::GetLuaObjType(const char* sName)
{
   if (m_listlot.empty()==false)
   {
      for(m_listlot_i=m_listlot.begin(); m_listlot_i!=m_listlot.end(); ++m_listlot_i)
      {
         if(m_listlot_i->sName==sName)
            return *m_listlot_i;
      }
   }
}
void lua_engine::CallScript(lua_obj* loSource, lua_obj* loTarget)
{
   if(m_listlscr.empty()==false)
   {
      for (m_listlscr_i = m_listlscr.begin();  m_listlscr_i!=m_listlscr.end(); ++m_listlscr_i)
      {
         if (loSource->m_lpotType==(*m_listlscr_i).lpotSource && loTarget->m_lpotType==(*m_listlscr_i).lpotTarget)
         {
            lua_getglobal(m_lState,(*m_listlscr_i).sFunction);
            lua_getglobal(m_lState,loSource->m_lptData->m_sName);
            lua_getglobal(m_lState,loTarget->m_lptData->m_sName);
            lua_call(m_lState,2,0);
         }
      }
   }
}
void lua_engine::AssignScript(const char* sFunction, lua_obj_type* lpotSource, lua_obj_type* lpotTarget)
{
   lua_script lScript;
   lScript.sFunction = sFunction;
   lScript.lpotSource = lpotSource;
   lScript.lpotTarget = lpotTarget;
   m_listlscr.push_back(lScript);
}
void lua_engine::AssignScript(const char* sFunction, const char* sSource, const char* sTarget)
{
   lua_script lScript;
   lScript.sFunction = sFunction;
   lScript.lpotSource = &GetLuaObjType(sSource);
   lScript.lpotTarget = &GetLuaObjType(sTarget);
   m_listlscr.push_back(lScript);
}
 void lua_engine::RegisterCppFunction(const char* sFunction, lua_CFunction fn)
 {
    lua_register(m_lState,sFunction,fn);
 }
