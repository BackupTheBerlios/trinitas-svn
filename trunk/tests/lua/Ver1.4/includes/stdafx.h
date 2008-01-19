#ifndef STDAFX
#define STDAFX
#include <iostream>
#include <list.h>
int sizeofchar(const char* String);
extern "C"
{
   #include <lua.h>
   #include <lualib.h>
   #include <lauxlib.h>
}
#include "lua_obj_type.h"
#include "lua_script.h"
#include "lua_table.h"
#include "lua_obj.h"
#include "lua_engine.h"
#include "ctvar.h"

#endif
