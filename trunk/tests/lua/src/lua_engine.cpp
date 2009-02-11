#include "lua_engine.h"

lua_engine* lua_plugin::m_lEngine = NULL;
lua_plugin* lua_plugin::m_lPlugin = NULL;


lua_plugin::lua_plugin()
{
   mID = (int)123;
   m_lPlugin = this;
}
char* lua_plugin::GetName()
{
   return "Lua Plugin v1.0";
}
inline lua_plugin* lua_plugin::Get()
{
   return m_lPlugin;
}
void* lua_plugin::Do()
{
   m_lEngine = new lua_engine;
   return (void*) m_lEngine;
}
void lua_plugin::Close()
{
   delete(m_lEngine);
   m_lEngine = NULL;
}





lua_engine* lua_engine::m_lEngine = NULL;


// Starts and initializes the engine
lua_engine::lua_engine()
{
   m_lEngine = this;
   m_lState=lua_open();
   luaL_openlibs(m_lState);
   lua_register(m_lState, "RegisterObject", lua_engine::lib_RegisterObject);
//   lua_register(m_lState, "Check", lua_engine::checkstack);
   lua_register(m_lState, "StartEventUsewith", lua_event::usewith::lib_Init);
}

// Stops the engine and releases the memory
lua_engine::~lua_engine()
{
   lua_close(m_lState);
   m_lState = NULL;
}


// Opens a library with c++ functions for lua
void lua_engine::OpenLibrary(void (*fp)(lua_State*))
{
   fp(m_lState);
}
// Parses a file
void lua_engine::ParseFile(const char* sFile)
{
   luaL_loadfile(m_lState,sFile);
   lua_call(m_lState, 0, LUA_MULTRET);
}

// Registers a function which is then accessable from Lua
void lua_engine::RegisterFunction(const char* sFunction, lua_CFunction fn)
 {
    lua_register(m_lState,sFunction,fn);
 }

// Defines the function that is called when Lua gets a panic error
void lua_engine::SetPanicFunction(lua_CFunction panicf)
{
   lua_atpanic(m_lState,panicf);
}

lua_obj* lua_engine::RegisterObject()
{
   lua_obj* newObj = (lua_obj*) lua_topointer(m_lState, -1);
   lua_pushlightuserdata(m_lState,&newObj->key);
   lua_pushvalue(m_lState, -2);
   lua_remove(m_lState, -3);
   lua_settable( m_lState, LUA_REGISTRYINDEX );
   m_listlo.push_back(newObj);
   return newObj;
}

void lua_engine::CallLuaMethod(const char* sLuaClass, const char* sMethod, char* format, ... )
{
   lua_getglobal(m_lState,sLuaClass);
   lua_pushstring(m_lState, sMethod);
   lua_gettable(m_lState, -2);
   lua_pushvalue(m_lState, -2);
   lua_remove(m_lState,-3);
   va_list argptr;
   va_start( argptr, format );
   int n = pushvarg(format, &argptr);
   va_end( argptr);
   lua_call(m_lState, n+1, LUA_MULTRET);

}
lua_obj* lua_engine::CreateCharacter(const char* sRace, const char* sLanguage)
{
   CallLuaMethod("character","new","ss",sRace,sLanguage);
   lua_obj* myObj = (lua_obj*)lua_topointer(m_lState, -1);
   lua_remove(m_lState, -1);
   return myObj;
}
lua_obj* lua_engine::CreateItem(const char* sType)
{
   CallLuaMethod("item","new","s",sType);
   lua_obj* myObj = (lua_obj*)lua_topointer(m_lState, -1);
   lua_remove(m_lState, -1);
   return myObj;
}

// Calls the Lua function with two objects
void lua_engine::Use(lua_obj* pUser, lua_obj* pSource, lua_obj* pTarget)
{
   pushobject(pSource);
   lua_getfield(m_lState, -1, "type");
   lua_getfield(m_lState, -1, "usewith");
   lua_remove(m_lState,-2);
   lua_pushnumber(m_lState, pTarget->GetTypeId());
   lua_gettable(m_lState, -2);
   lua_remove(m_lState,-2);
   if ( lua_isnil(m_lState,-1)==true)
   {
      lua_pop(m_lState,2);
      return;
   }
   pushobject(pUser);
   lua_pushvalue(m_lState, -3);
   lua_remove(m_lState, -4);
   pushobject(pTarget);
   lua_call(m_lState,3,0);
}

lua_event* lua_engine::StartEvent(int difTime)
{
   lua_event* newEvent = new lua_event;
   newEvent->m_Time = difTime;
   newEvent->m_timeStamp = clock();
   return newEvent;
}
const char* lua_engine::getobjectstring(lua_obj* loObj, const char* sVar)
{
   pushobject(loObj);
   getluavar(sVar);
   return lua_tostring(m_lState, -1);
}
void lua_engine::getluavar(const char* sVar)
{
   char* buffer = new char[40];
   sprintf(buffer,"");
   int bI;
   bool endloop=false;
   for(int i=0;endloop==false;i++)
   {
      if(sVar[i]!='.' && sVar[i]!='\0')
      {
          sprintf(buffer,"%s%c",buffer,sVar[i]);
          bI++;
      }
      else
      {
          lua_getfield(m_lState, -1, buffer);
          lua_remove(m_lState, -2);
          sprintf(buffer,"");
          bI=0;
          if(sVar[i]=='\0')
              endloop=true;
      }
   }
}


int lua_engine::getobjectnumber(lua_obj* loObj, const char* sVar)
{
   pushobject(loObj);
   getluavar(sVar);
   int i = (int)lua_tonumber(m_lState, -1);
   lua_remove(m_lState, -1);
   return i;
}


int lua_engine::getobjectboolean(lua_obj* loObj, const char* sVar)
{
   pushobject(loObj);
   getluavar(sVar);
   return lua_toboolean(m_lState, -1);
}


void* lua_engine::getobjectpointer(lua_obj* loObj, const char* sVar)
{
   pushobject(loObj);
   getluavar(sVar);
   return (void*)lua_topointer(m_lState, -1);
}


void lua_engine::CreateItemType(const char* sName)
{
   CallLuaMethod("itemtype","new","sd",sName);
}


// Language functions
void lua_engine::AddWords(const char* sVar, const char* sWords, const char* sShort)
{
   CallLuaMethod("language","get","s",sShort);
   lua_pushstring(m_lState,sVar);
   lua_pushstring(m_lState,sWords);
   lua_settable(m_lState,-3);
   lua_remove(m_lState,-1);
}
const char* lua_engine::GetWords(const char* sVar, const char* sShort)
{
   CallLuaMethod("language","get","s",sShort);
   getluavar(sVar);
   lua_remove(m_lState,-2);
   const char* sWords = lua_tostring(m_lState,-1);
   lua_remove(m_lState,-1);
   return sWords;
}


// Event functions
void lua_engine::CheckEvents()
{
   if(m_listlev.size()==0)
      return;
   m_curTime = clock();
   for(m_listlev_i = m_listlev.begin();m_listlev_i!=m_listlev.end();m_listlev_i++)
   {
      lua_event* myEvent = *m_listlev_i;
      if(difftime(m_curTime,myEvent->m_timeStamp)>=myEvent->m_Time)
      {
         myEvent->Execute();
         m_listlev.erase(m_listlev_i);
         CheckEvents();
         return;
      }
   }
}

int lua_engine::lib_RegisterObject(lua_State* L)
{
   g_lEngine->RegisterObject();
   return 0;
}
void lua_engine::pushobject(lua_obj* loObj)
{
   lua_pushlightuserdata(m_lState, &loObj->key);
   lua_gettable(m_lState, LUA_REGISTRYINDEX);
}

va_list* lua_engine::tovarg(char* format, ...)
{
   va_list* argptr = new va_list;
   va_start(*argptr, format );
   return argptr;
}
int lua_engine::pushvarg(char* format,va_list* argptr)
{
   int n = 0;
   while( *format != '\0' )
   {
      n++;
      switch (*format)
      {
         case 'd':
         case 'i': // number or integer
            lua_pushnumber(m_lState, va_arg(*argptr, int) );
            break;
         case 'b':  //boolean
            lua_pushboolean(m_lState, va_arg(*argptr, int) );
            break;
         case 'c':  //character
            lua_pushboolean(m_lState, va_arg(*argptr, int) );
            break;
         case 's':
            lua_pushstring(m_lState, va_arg(*argptr, char*));
            break;
         case 'O':
            pushobject(va_arg(*argptr, lua_obj*));
            break;
         default:
            lua_pushlightuserdata(m_lState, va_arg(*argptr, void*) );
            break;
      }
      *format++;
   }
   return n;
}


int lua_engine::checkstack()
{
   int i;
   int top = lua_gettop(m_lState);
   printf("-----------\n");
   for (i = 1; i<=top; i++) {
      int t = lua_type(m_lState, i);
      printf("#%d [#%d]   ",i, - (top - i + 1));
      switch(t) {
         case LUA_TSTRING:
            printf("String: '%s'", lua_tostring(m_lState, i));
            break;
         case LUA_TBOOLEAN:
            printf("Bool: %s",lua_toboolean(m_lState, i) ? "true" : "false");
            break;
         case LUA_TNUMBER:
            printf("Number: %g",lua_tonumber(m_lState, i));
            break;
         default:
            printf("Unknown <%s>",lua_typename(m_lState, t));
            break;
      }
      printf(" [%d]\n", lua_topointer(m_lState, i));
   }
   return 0;
}
