class luac_interface
{
public:
    lua_State* lState;

    lua_State* State();
    int luac_interface::get_lua_iVar(char * myvar);
    luac_interface();
    ~luac_interface();

};
