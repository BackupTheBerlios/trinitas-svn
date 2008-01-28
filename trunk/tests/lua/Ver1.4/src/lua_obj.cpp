#include "lua_engine.h"

lua_obj::lua_obj()
{
   m_lptData = new lua_Table;
   m_lptData->Update();
}
lua_obj::lua_obj(lua_obj_type* lpotType)
{
   m_lptData = new lua_Table;
   AssignObjType(lpotType);
   m_lptData->Update();
}
const char* lua_obj::TableName()
{
   return m_lptData->m_sName;
}
void lua_obj::AssignObjType(lua_obj_type* lpotType)
{
   m_lpotType = lpotType;
   m_lptData->NewStringEntry("type",lpotType->m_sName);
}
lua_Table* lua_obj::GetTable()
{
   return m_lptData;
}
void lua_obj::CheckType()
{
   lua_obj_type* lpotTemp;
   lpotTemp = m_lpotType;
   m_lptData->GetTableEntry("type");
   const char* sType = lua_tostring(g_lState,-1);
   m_lpotType = g_lEngine->GetLuaObjType(sType);
   if (m_lpotType==NULL)
      m_lpotType = lpotTemp;
}