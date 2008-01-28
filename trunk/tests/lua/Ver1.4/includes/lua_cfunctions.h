#ifndef LUA_FUNCTIONS
#define LUA_FUNCTIONS

#include "lua_var.h"
#include <iostream>

int checkmystack(lua_State* L);
static void* checkmetatable(lua_State* L, const char* sName);

///
/// Creates a new character
///
static int lualib_newcharacter (lua_State* L)
{
   lua_engine::Get()->CreateCharacter(lua_tostring(L,-1));
   return 1;
}

///
/// Returns the data table of a character
///
static int lualib_getcharactertable(lua_State* L)
{
   lua_obj* myChar = (lua_obj*) checkmetatable(L, "character");
   lua_getglobal(L, myChar->TableName());
   return 1;
}

static const struct luaL_reg characterlib_f [] = {
   {"new", lualib_newcharacter},
   {NULL, NULL}
};
static const struct luaL_reg characterlib_m [] = {
   {"data", lualib_getcharactertable},
   {NULL, NULL}
};


///
/// Creates a new item
///
static int lualib_newitem (lua_State* L)
{
   lua_engine::Get()->CreateItem(lua_tostring(L,-1));
   return 1;
}

///
/// Returns the data table of an item
///
static int lualib_getitemtable(lua_State* L)
{
   lua_obj* myItem = (lua_obj*) checkmetatable(L, "item");
   lua_getglobal(L, myItem->TableName());
   return 1;
}

static const struct luaL_reg itemlib_f [] = {
   {"new", lualib_newitem},
   {NULL, NULL}
};
static const struct luaL_reg itemlib_m [] = {
   {"data", lualib_getitemtable},
   {NULL, NULL}
};


void lualib_character (lua_State* L)
{
   luaL_newmetatable(L, "LuaBook.character");
   lua_pushstring(L, "__index");
   lua_pushvalue(L, -2);
   lua_settable(L, -3);
   luaL_register(L, NULL, characterlib_m);
   luaL_register(L, "character", characterlib_f);
}
void lualib_item (lua_State* L)
{
   luaL_newmetatable(L, "LuaBook.item");
   lua_pushstring(L, "__index");
   lua_pushvalue(L, -2);
   lua_settable(L, -3);
   luaL_openlib(L, NULL, itemlib_m, 0);
   luaL_openlib(L, "item", itemlib_f, 0);
}

static void* checkmetatable(lua_State* L, const char* sName)
{
   char* mtName = new char[50];
   char* errorMsg = new char[50];
   sprintf(mtName,"LuaBook.%s",sName);
   sprintf(errorMsg,"`%s' expected",sName);
   void* ud = luaL_checkudata(L, -1, mtName);
   luaL_argcheck(L, ud != NULL, 1, errorMsg);
   delete(mtName);
   delete(errorMsg);
   return ud;
}

#endif
