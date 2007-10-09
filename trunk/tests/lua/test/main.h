int get_int_var(lua_State *L, char * myvar);

class luac_interface
{
public:
    lua_State* lState;

    lua_State* State();
    int luac_interface::get_lua_iVar(char * myvar);
    luac_interface();
    ~luac_interface();

};

lua_State* luac_interface::State()
{
    return lState;
}
int luac_interface::get_lua_iVar(char * myvar)
{
    lua_pushstring(lState, myvar);
    lua_gettable(lState,LUA_GLOBALSINDEX);
    int result = (int)lua_tonumber(lState,-1);
    return result;
}
luac_interface::luac_interface()
{
    lua_State* lState = lua_open();
    luaL_openlibs(lState);
}

luac_interface::~luac_interface()
{
    lua_close(lState);
}
int get_lua_iVar(lua_State* lState, char * myvar)
{
    lua_pushstring(lState, myvar);
    lua_gettable(lState,LUA_GLOBALSINDEX);
    int result = (int)lua_tonumber(lState,-1);
    return result;
}
void CallLuaFunction(lua_State* lState, const char* fncName, int nResults, ...)
{
    int i;
    char* param;
    lua_getfield(L, LUA_GLOBALSINDEX, fncName);
    va_list args;
    va_start(args,param);
    while(param!=NULL)
    {
        i++;
        lua_pushstring(lState,param);
        param = va_arg(args,char*);
    }
    va_end(args);
    lua_call(lState,i,nResults);
}
int GetReturnValue(lua_State* lState)
{
    lua_gettable(lState,LUA_GLOBALSINDEX);
    int result = (int)lua_tonumber(lState,-1);
    return result;
}
int GetReturnValue(lua_State* lState, int index)
{
    lua_gettable(lState,LUA_GLOBALSINDEX);
    int result = (int)lua_tonumber(lState,index-1);
    return result;
}
