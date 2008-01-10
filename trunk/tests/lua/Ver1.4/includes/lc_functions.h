void lc_init(lua_State* lState);
int lc_CreateObjectType(lua_State* lState);
int lc_CreateObject(lua_State* lState);
void lua_getarray(lua_State* lState, const char* sArray, int id);
void lua_getarraysfield(lua_State* lState, const char* sArray, int id,const char* sValue);
void printfLTop(lua_State* L);

class lua_Obj
{
public:
   lua_State* lState;
   lua_Table tTab;
   int id;
   lua_Obj(lua_State* L, int nId);
   void DoFile();
   void UseWith(lua_Obj* targObj);
   const char* TableName();
   void ScriptUpdate();
   void TableUpdate();
};
lua_Obj::lua_Obj(lua_State* L, int nId)
: id (nId), lState(L)
{
   lua_Table nTab(lState);
   nTab.NewNumberEntry("id",nId);
   nTab.Update();
   tTab = nTab;
}
void lua_Obj::DoFile()
{
   lua_getarraysfield(lState,"obj",id,"script");
   const char* sName = lua_tostring(lState,-1);
   lua_remove(lState,-1);
   char sExeName[64];
   sprintf(sExeName,"scripts/%s",sName);
   luaL_dofile(lState,sExeName);
}
void lua_Obj::UseWith(lua_Obj* targObj)
{
   lua_getglobal(lState, "UseItem");
   lua_getglobal(lState,TableName());
   lua_getglobal(lState,targObj->tTab.tName);
   lua_call(lState,2,0);
   ScriptUpdate();
   targObj->ScriptUpdate();
}
const char* lua_Obj::TableName()
{
   return tTab.tName;
}
void lua_Obj::ScriptUpdate()
{
   tTab.GetTableEntry("id");
   this->id = lua_tointeger(lState,-1);
}
void lua_Obj::TableUpdate()
{
   tTab.NewNumberEntry("id", id);
}
void lc_init(lua_State* lState)
{
   lua_register(lState,"CreateObject",lc_CreateObject);
}
int lc_CreateObject(lua_State* lState)
{
   int idObj = lua_tointeger(lState,1);
   lua_Obj lObj(lState,idObj);
   lua_getglobal(lState,lObj.tTab.tName);
   return 1;
}
// return:  array[id]
void lua_getarray(lua_State* lState, const char* sArray, int id)
{
   lua_getglobal(lState,sArray);
   lua_pushinteger(lState,id);
   lua_gettable(lState,-2);
   lua_remove(lState,-3);

// return:  array[id].value
}void lua_getarraysfield(lua_State* lState, const char* sArray, int id, const char* sValue)
{
   lua_getglobal(lState,sArray);
   lua_pushinteger(lState,id);
   lua_gettable(lState,-2);
   lua_remove(lState,-3);
   lua_getfield(lState,-1,sValue);
   lua_remove(lState,-2);
}
void printfLTop(lua_State* L)
{
   printf("Current Top:%i\n",lua_gettop(L));
}
