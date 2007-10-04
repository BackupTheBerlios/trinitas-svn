extern "C"
{
   #include "lua\src\lua.h"
   #include "lua\src\lualib.h"
   #include "lua\src\lauxlib.h"
}

int main()
{
      //initalise a lua state
      lua_State *L = lua_open();

      //close this current lua state
      lua_close(L);
      return 1;
}


