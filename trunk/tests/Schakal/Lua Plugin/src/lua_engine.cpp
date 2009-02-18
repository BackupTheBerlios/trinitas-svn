
/*
 * Copyright 2007 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 *
 * @autor    David Jablonski, davidjablonski@web.de
 * @date     14.02.2009
 */


#include "lua_engine.h"


LuaPlugin* LuaPlugin::mlPlugin = NULL;


LuaPlugin::LuaPlugin(long ID)
{
    mID = ID;
    mlPlugin = this;
}


LuaPlugin::~LuaPlugin()
{
    lua_close(mlState);
    mlState = NULL;
}


char* LuaPlugin::GetName()
{
    return "Lua Plugin";
}


inline LuaPlugin* LuaPlugin::Get()
{
    return mlPlugin;
}


void LuaPlugin::Do()
{
    mlState = lua_open();
    luaL_openlibs(mlState);
    lua_register(mlState, "RegisterObject", LuaPlugin::lib_RegisterObject);
//    lua_register(mlState, "Check", LuaPlugin::checkstack);
    lua_register(mlState, "StartEventUsewith", LuaEvent::usewith::lib_Init);
}


// Opens a library with c++ functions for lua
void LuaPlugin::OpenLibrary(void (*fp)(lua_State*))
{
    fp(mlState);
}


void LuaPlugin::ParseFile(const char* sFile)
{
    luaL_loadfile(mlState,sFile);
    lua_call(mlState, 0, LUA_MULTRET);
}


// Registers a function which is then accessable from Lua
void LuaPlugin::RegisterFunction(const char* sFunction, lua_CFunction fn)
{
    lua_register(mlState,sFunction,fn);
}


// Defines the function that is called when Lua gets a panic error
void LuaPlugin::SetPanicFunction(lua_CFunction panicf)
{
    lua_atpanic(mlState,panicf);
}


LuaObj* LuaPlugin::RegisterObject()
{
    LuaObj* object = (LuaObj*)lua_topointer(mlState, -1);
    lua_pushlightuserdata(mlState,&object->mKey);
    lua_pushvalue(mlState, -2);
    lua_remove(mlState, -3);
    lua_settable( mlState, LUA_REGISTRYINDEX );
    mListlo.push_back(object);
    return object;
}


void LuaPlugin::CallLuaMethod(const char* sLuaClass, const char* sMethod, char* format, ... )
{
    lua_getglobal(mlState,sLuaClass);
    lua_pushstring(mlState, sMethod);
    lua_gettable(mlState, -2);
    lua_pushvalue(mlState, -2);
    lua_remove(mlState,-3);
    va_list argptr;
    va_start( argptr, format );
    int n = PushVarg(format, &argptr);
    va_end( argptr);
    lua_call(mlState, n+1, LUA_MULTRET);
}


LuaObj* LuaPlugin::CreateCharacter(const char* sRace, const char* sLanguage)
{
   CallLuaMethod("character","new","ss",sRace,sLanguage);
   LuaObj* object = (LuaObj*)lua_topointer(mlState, -1);
   lua_remove(mlState, -1);
   return object;
}


LuaObj* LuaPlugin::CreateItem(const char* sType)
{
   CallLuaMethod("item","new","s",sType);
   LuaObj* object = (LuaObj*)lua_topointer(mlState, -1);
   lua_remove(mlState, -1);
   return object;
}


// Calls the Lua function with two objects
void LuaPlugin::Use(LuaObj* pUser, LuaObj* pSource, LuaObj* pTarget)
{
   PushObject(pSource);
   lua_getfield(mlState, -1, "type");
   lua_getfield(mlState, -1, "usewith");
   lua_remove(mlState,-2);
   lua_pushnumber(mlState, pTarget->GetTypeId());
   lua_gettable(mlState, -2);
   lua_remove(mlState,-2);
   if (lua_isnil(mlState,-1)) {
      lua_pop(mlState,2);
      return;
   }
   PushObject(pUser);
   lua_pushvalue(mlState, -3);
   lua_remove(mlState, -4);
   PushObject(pTarget);
   lua_call(mlState,3,0);
}


LuaEvent* LuaPlugin::StartEvent(int difTime)
{
   LuaEvent* newEvent = new LuaEvent;
   newEvent->mTime = difTime;
   newEvent->mTimeStamp = clock();
   return newEvent;
}


char* LuaPlugin::GetObjectString(LuaObj* loObj, const char* sVar)
{
   PushObject(loObj);
   GetLuaVar(sVar);
   return const_cast<char*>(lua_tostring(mlState, -1));
}


// Parses expressions like Spieler.Position.X
// and places the value on the top of the stack
void LuaPlugin::GetLuaVar(const char* sVar)
{
   char* buffer = new char[40];
   sprintf(buffer,"");
   int bI;
   bool endloop=false;
   for(int i=0;endloop==false;i++) {
      if(sVar[i]!='.' && sVar[i]!='\0') {
          sprintf(buffer,"%s%c",buffer,sVar[i]);
          bI++;
      }
      else {
          lua_getfield(mlState, -1, buffer);
          lua_remove(mlState, -2);
          sprintf(buffer,"");
          bI=0;
          if(sVar[i]=='\0')
              endloop=true;
      }
   }
}


int LuaPlugin::GetObjectNumber(LuaObj* loObj, const char* sVar)
{
   PushObject(loObj);
   GetLuaVar(sVar);
   int i = (int)lua_tonumber(mlState, -1);
   lua_remove(mlState, -1);
   return i;
}


char LuaPlugin::GetObjectBoolean(LuaObj* loObj, const char* sVar)
{
   PushObject(loObj);
   GetLuaVar(sVar);
   char b = static_cast<char>(lua_toboolean(mlState, -1));
   lua_remove(mlState, -1);
   return b;
}


void* LuaPlugin::GetObjectPointer(LuaObj* loObj, const char* sVar)
{
   PushObject(loObj);
   GetLuaVar(sVar);
   return (void*)lua_topointer(mlState, -1);
}


void LuaPlugin::CreateItemType(const char* sName)
{
   CallLuaMethod("itemtype","new","sd",sName);
}


// Language functions
void LuaPlugin::AddWords(const char* sVar, const char* sWords, const char* sShort)
{
   CallLuaMethod("language","get","s",sShort);
   lua_pushstring(mlState,sVar);
   lua_pushstring(mlState,sWords);
   lua_settable(mlState,-3);
   lua_remove(mlState,-1);
}


const char* LuaPlugin::GetWords(const char* sVar, const char* sShort)
{
   CallLuaMethod("language","get","s",sShort);
   GetLuaVar(sVar);
   lua_remove(mlState,-2);
   const char* sWords = lua_tostring(mlState,-1);
   lua_remove(mlState,-1);
   return sWords;
}


// Event functions
void LuaPlugin::CheckEvents()
{
   if(mListlev.size()==0)
      return;
   mCurTime = clock();
   for(mListlevI = mListlev.begin();mListlevI!=mListlev.end();mListlevI++) {
      LuaEvent* lEvent = *mListlevI;
      if(difftime(mCurTime,lEvent->mTimeStamp)>=lEvent->mTime) {
         lEvent->Execute();
         mListlev.erase(mListlevI);
         CheckEvents();
         return;
      }
   }
}


int LuaPlugin::lib_RegisterObject(lua_State* L)
{
   glPlugin->RegisterObject();
   return 0;
}


void LuaPlugin::PushObject(LuaObj* loObj)
{
   lua_pushlightuserdata(mlState, &loObj->mKey);
   lua_gettable(mlState, LUA_REGISTRYINDEX);
}


va_list* LuaPlugin::ToVarg(char* format, ...)
{
   va_list* argptr = new va_list;
   va_start(*argptr, format );
   return argptr;
}


int LuaPlugin::PushVarg(char* format,va_list* argptr)
{
   int n = 0;
   while( *format != '\0' ) {
      n++;
      switch (*format) {
         case 'd':
         case 'i': // number or integer
            lua_pushnumber(mlState, va_arg(*argptr, int) );
            break;
         case 'b':  //boolean
            lua_pushboolean(mlState, va_arg(*argptr, int) );
            break;
         case 'c':  //character
            lua_pushboolean(mlState, va_arg(*argptr, int) );
            break;
         case 's':
            lua_pushstring(mlState, va_arg(*argptr, char*));
            break;
         case 'O':
            PushObject(va_arg(*argptr, LuaObj*));
            break;
         default:
            lua_pushlightuserdata(mlState, va_arg(*argptr, void*) );
            break;
      }
      *format++;
   }
   return n;
}


int LuaPlugin::CheckStack()
{
   int i;
   int top = lua_gettop(mlState);
   printf("-----------\n");
   for (i = 1; i<=top; i++) {
      int t = lua_type(mlState, i);
      printf("#%d [#%d]   ",i, - (top - i + 1));
      switch(t) {
         case LUA_TSTRING:
            printf("String: '%s'", lua_tostring(mlState, i));
            break;
         case LUA_TBOOLEAN:
            printf("Bool: %s",lua_toboolean(mlState, i) ? "true" : "false");
            break;
         case LUA_TNUMBER:
            printf("Number: %g",lua_tonumber(mlState, i));
            break;
         default:
            printf("Unknown <%s>",lua_typename(mlState, t));
            break;
      }
      printf(" [%d]\n", lua_topointer(mlState, i));
   }
   return 0;
}
