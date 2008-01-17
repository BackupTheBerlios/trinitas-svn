#ifndef LUAENGINE
#define LUAENGINE
#include "singletons.h"
#define g_lState lua_engine::Get()->lState

class lua_engine : public TSingleton<lua_engine>
{
public:
   lua_State* lState;
   void Start();
   void Release();
   void ParseFile(const char* sName);
};
#endif

