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

