#include "stdafx.h"

void lua_engine::Start()
{
   m_lState=lua_open();
   luaL_openlibs(m_lState);
   m_pSingleton = this;
}
void lua_engine::Release()
{
   lua_close(m_lState);
   m_lState = NULL;
   m_listlpot.clear();
   m_listlscr.clear();
}
void lua_engine::ParseFile(const char* sFile)
{
   luaL_dofile(m_lState,sFile);
}
lua_obj_type* lua_engine::AddLuaObjType(const char* sName)
{
   lua_obj_type* lpObjType = new lua_obj_type();
   lpObjType->m_sName = sName;
   m_listlpot.push_back(lpObjType);
   return lpObjType;
}
lua_obj_type* lua_engine::GetLuaObjType(const char* sName)
{
   printf("---------Get Lua Obj Type-------------\n");
   printf("Search for %s with %i chars\n",sName,sizeofchar(sName));
   if (m_listlpot.empty()==false)
   {
      for(m_listlpot_i=m_listlpot.begin(); m_listlpot_i!=m_listlpot.end(); ++m_listlpot_i)
      {
         printf("Compare %s with %s \n",(*m_listlpot_i)->m_sName,sName);
         if((*m_listlpot_i)->m_sName==sName)
         {
            printf("You found it!!\n");
            return *m_listlpot_i;
         }
      }
   }
}
void lua_engine::CallScript(lua_obj* loSource, lua_obj* loTarget)
{
   if(m_listlscr.empty()==false)
   {
      for (m_listlscr_i = m_listlscr.begin();  m_listlscr_i!=m_listlscr.end(); ++m_listlscr_i)
      {
         if (loSource->m_lpotType==(*m_listlscr_i).m_lpotSource && loTarget->m_lpotType==(*m_listlscr_i).m_lpotTarget)
         {
            lua_getglobal(m_lState,(*m_listlscr_i).m_sFunction);
            lua_getglobal(m_lState,loSource->m_lptData->m_sName);
            lua_getglobal(m_lState,loTarget->m_lptData->m_sName);
            lua_call(m_lState,2,0);
            loSource->CheckType();
            loTarget->CheckType();
         }
      }
   }
}
void lua_engine::AssignScript(const char* sFunction, lua_obj_type* lpotSource, lua_obj_type* lpotTarget)
{
   lua_script lScript;
   lScript.m_sFunction = sFunction;
   lScript.m_lpotSource = lpotSource;
   lScript.m_lpotTarget = lpotTarget;
   m_listlscr.push_back(lScript);
}
void lua_engine::AssignScript(const char* sFunction, const char* sSource, const char* sTarget)
{
   AssignScript(sFunction,GetLuaObjType(sSource),GetLuaObjType(sTarget));
}
 void lua_engine::RegisterCppFunction(const char* sFunction, lua_CFunction fn)
 {
    lua_register(m_lState,sFunction,fn);
 }
