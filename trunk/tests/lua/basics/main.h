//int get_int_var(lua_State *L, char * myvar);

class luac_interface
{
public:
    lua_State* lState;

    lua_State* State();
    lua_State* Start();
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
