#include "stdafx.h"

lua_Obj::lua_Obj(int nId)
{
   id = nId;
   TableUpdate();
   tTab->Update();
}
void lua_Obj::DoFile()
{
   lua_getarraysfield("obj",id,"script");
   const char* sName = lua_tostring(g_lState,-1);
   lua_remove(g_lState,-1);
   char sExeName[64];
   sprintf(sExeName,"scripts/%s",sName);
   luaL_dofile(g_lState,sExeName);
}
void lua_Obj::UseWith(lua_Obj* targObj)
{
   lua_getglobal(g_lState, "UseItem");
   lua_getglobal(g_lState,TableName());
   lua_getglobal(g_lState,targObj->tTab->tName);
   lua_call(g_lState,2,0);
   ScriptUpdate();
   targObj->ScriptUpdate();
}
const char* lua_Obj::TableName()
{
   return tTab->tName;
}
void lua_Obj::ScriptUpdate()
{
   tTab->GetTableEntry("id");
   id = lua_tointeger(g_lState,-1);
}
void lua_Obj::TableUpdate()
{
   tTab->NewNumberEntry("id", id);
}
