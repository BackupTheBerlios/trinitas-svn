extern "C"
{
   #include "lua.h"
   #include "lualib.h"
   #include "lauxlib.h"
}

int main()
{
      //initalise a lua state
      lua_State *L = lua_open();

      //close this current lua state
      lua_close(L);
      return 1;
}


