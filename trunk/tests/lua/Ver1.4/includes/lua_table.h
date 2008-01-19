#ifndef LUA_TABLE
#define LUA_TABLE
#include "stdafx.h"
class lua_Table
{
public:
   static int s_iIndex;
   char* m_sName;
   lua_Table();
   void NewNumberEntry(const char* sVar, int iValue);
   void NewStringEntry(const char* sVar, const char* sValue);
   void NewTableEntry(const char* sVar, lua_Table* lptData);
   void NewNilEntry(const char* sVar);
   void GetTableEntry(const char* sVar);
   void InsertValues();
   void Update();
};
#endif
