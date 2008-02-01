#ifndef LUA_FUNCTIONS
#define LUA_FUNCTIONS


static void* checkmetatable(lua_State* L, const char* sName);


static void* checkmetatable(lua_State* L, const char* sName)
{
   char* errorMsg = new char[50];
   sprintf(errorMsg,"`%s' expected",sName);
   void* ud = luaL_checkudata(L, -1, sName);
   luaL_argcheck(L, ud != NULL, 1, errorMsg);
   delete(errorMsg);
   return ud;
}

#endif
