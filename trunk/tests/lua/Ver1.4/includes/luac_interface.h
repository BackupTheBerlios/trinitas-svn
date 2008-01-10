class lua_Table
{
public:
   static int iIndex;
   char* tName;
   lua_State* lState;
   lua_Table() {}
   lua_Table(lua_State* L);
   void NewNumberEntry(const char* sName, int iValue);
   void NewStringEntry(const char* sName, const char* sValue);
   void NewTableEntry(const char* sName, lua_Table* tTab);
   void NewNilEntry(const char* sName);
   void GetTableEntry(const char* sName);
   void InsertValues();
   void Update();
};
int lua_Table::iIndex=0;
lua_Table::lua_Table(lua_State* L)
{
   lua_Table::iIndex++;
   tName = new char(20);
   sprintf(tName,"tab%i",lua_Table::iIndex);
   lState = L;
   lua_newtable(L);
}
void lua_Table::NewNumberEntry(const char* sName, int iValue)
{
   lua_pushstring(this->lState,sName);
   lua_pushnumber(this->lState, iValue);
   lua_rawset(this->lState,-3);
}
void lua_Table::NewStringEntry(const char* sName, const char* sValue)
{
   lua_pushstring(this->lState,sName);
   lua_pushstring(this->lState,sValue);
   lua_rawset(this->lState,-3);
}
void lua_Table::NewTableEntry(const char* sName, lua_Table* tTab)
{
   lua_pushstring(this->lState,sName);
   lua_getglobal(this->lState,tTab->tName);
   lua_rawset(this->lState,-3);

}
void lua_Table::NewNilEntry(const char* sName)
{
   lua_pushstring(this->lState,sName);
   lua_pushnil(this->lState);
   lua_rawset(this->lState,-3);
}
void lua_Table::InsertValues()
{
   lua_getglobal(this->lState,this->tName);
}
void lua_Table::Update()
{
   lua_setglobal(this->lState,this->tName);
}
void lua_Table::GetTableEntry(const char* sName)
{
   lua_getglobal(this->lState,this->tName);
   lua_getfield(this->lState,-1,sName);
   lua_remove(this->lState,-2);
}

