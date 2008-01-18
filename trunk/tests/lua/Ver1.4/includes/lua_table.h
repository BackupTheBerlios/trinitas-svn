#ifndef LUA_TABLE
#define LUA_TABLE
#include "stdafx.h"
class lua_Table
{
public:
   static int s_iIndex;
   char* m_sName;
   lua_Table();
   void NewNumberEntry(const char* sName, int iValue);
   void NewStringEntry(const char* sName, const char* sValue);
   void NewTableEntry(const char* sName, lua_Table* lptData);
   void NewNilEntry(const char* sName);
   void GetTableEntry(const char* sName);
   void InsertValues();
   void Update();
};
#endif
