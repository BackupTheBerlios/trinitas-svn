extern "C"
{
   #include <lua.h>
   #include <lualib.h>
   #include <lauxlib.h>
}

int main()
{
      //initalise a lua state
      lua_State *L = lua_open();
      luaopen_base(L);
      //luaopen_string(L);
      //luaopen_table(L);
      //luaopen_math(L);
      //luaopen_debug(L);
//      luaopen_io(L);
      luaL_loadfile(L,"main.lua");
      //close this current lua state
      lua_close(L);
      return 1;
}


