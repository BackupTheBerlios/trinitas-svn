#include "stdafx.h"

lua_obj::lua_obj(lua_obj_type* lpotType)
{
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
}
