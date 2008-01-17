#include "stdafx.h"
int lua_Table::iIndex=0;

lua_Table::lua_Table()
{
   lua_Table::iIndex++;
   tName = new char(20);
   sprintf(tName,"tab%i",lua_Table::iIndex);
   lua_newtable(g_lState);
}
void lua_Table::NewNumberEntry(const char* sName, int iValue)
{
   lua_pushstring(g_lState,sName);
   lua_pushnumber(g_lState, iValue);
   lua_rawset(g_lState,-3);
}
void lua_Table::NewStringEntry(const char* sName, const char* sValue)
{
   lua_pushstring(g_lState,sName);
   lua_pushstring(g_lState,sValue);
   lua_rawset(g_lState,-3);
}
void lua_Table::NewTableEntry(const char* sName, lua_Table* tTab)
{
   lua_pushstring(g_lState,sName);
   lua_getglobal(g_lState,tTab->tName);
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
   lua_getglobal(g_lState,tName);
}
void lua_Table::Update()
{
   lua_setglobal(g_lState,tName);
}
void lua_Table::GetTableEntry(const char* sName)
{
   lua_getglobal(g_lState,tName);
   lua_getfield(g_lState,-1,sName);
   lua_remove(g_lState,-2);
}
