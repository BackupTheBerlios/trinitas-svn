#include "stdafx.h"
int lua_Table::s_iIndex=0;

lua_Table::lua_Table()
{
   lua_Table::s_iIndex++;
   m_sName = new char(20);
   sprintf(m_sName,"tab%i",lua_Table::s_iIndex);
   lua_newtable(g_lState);
}
void lua_Table::NewNumberEntry(const char* sVar, int iValue)
{
   lua_pushstring(g_lState,sVar);
   lua_pushnumber(g_lState, iValue);
   lua_rawset(g_lState,-3);
}
void lua_Table::NewStringEntry(const char* sVar, const char* sValue)
{
   lua_pushstring(g_lState,sVar);
   lua_pushstring(g_lState,sValue);
   lua_rawset(g_lState,-3);
}
void lua_Table::NewTableEntry(const char* sVar, lua_Table* lptData)
{
   lua_pushstring(g_lState,sVar);
   lua_getglobal(g_lState,lptData->m_sName);
   lua_rawset(g_lState,-3);

}
void lua_Table::NewNilEntry(const char* sName)
{
   lua_pushstring(g_lState,sName);
   lua_pushnil(g_lState);
   lua_rawset(g_lState,-3);
}
void lua_Table::InsertValues()
{
   lua_getglobal(g_lState,m_sName);
}
void lua_Table::Update()
{
   lua_setglobal(g_lState,m_sName);
}
void lua_Table::GetTableEntry(const char* sVar)
{
   lua_getglobal(g_lState,m_sName);
   lua_getfield(g_lState,-1,sVar);
   lua_remove(g_lState,-2);
}

