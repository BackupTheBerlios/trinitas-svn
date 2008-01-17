#ifndef STDAFX
#define STDAFX
#include <iostream>

extern "C"
{
   #include <lua.h>
   #include <lualib.h>
   #include <lauxlib.h>
}

#include "lua_engine.h"
#include "ctvar.h"
#include "lc_functions.h"
#include "lua_table.h"
#include "lua_obj.h"
#endif
