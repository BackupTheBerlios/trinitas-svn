#include "lua_engine.h"

// Starts and initializes the engine
void lua_engine::Start()
{
   m_lState=lua_open();
   luaL_openlibs(m_lState);
   lua_register(m_lState, "RegisterObject", lib_RegisterObject);
   lua_register(m_lState, "Check", checkmystack);
   m_pSingleton = this;
}

// Stops the engine and releases the memory
void lua_engine::Release()
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
   luaL_dofile(m_lState,sFile);
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
   int n = lua_pushvarg(m_lState, format, &argptr);
   va_end( argptr);
   lua_call(m_lState, n+1, LUA_MULTRET);

}

lua_obj* lua_engine::CreateCharacter(const char* sRace)
{
   CallLuaMethod("character","new","s",sRace);
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
/*template <class T>

T toluavar(lua_State* m_lState,int index)
{
   switch(lua_type(m_lState,-1))
   {
      case LUA_TNIL:
         return NULL;
      case LUA_TBOOLEAN:
         return lua_toboolean(m_lState, -1);
      case LUA_TLIGHTUSERDATA:
         return lua_topointer(m_lState, -1);
      case LUA_TNUMBER:
         return lua_tonumber(m_lState, -1);
      case LUA_TSTRING:
         return lua_tostring(m_lState, -1);
      case LUA_TTABLE:
         return lua_topointer(m_lState, -1);
      case LUA_TFUNCTION:
         return lua_topointer(m_lState, -1);
      case LUA_TUSERDATA:
         return lua_topointer(m_lState, -1);
      case LUA_TTHREAD:
         return lua_topointer(m_lState, -1);
   }
}*/
// Calls the Lua function with two objects
void lua_engine::Use(lua_obj* pUser, lua_obj* pSource, lua_obj* pTarget)
{
   char* sFunctionName = new char[60];

   // Gets the name of the lua function:
   // Use[pSource.type]With[pTarget.type]
   lua_pushobject(m_lState, pSource);
   lua_getfield(m_lState, -1, "type");
   lua_getfield(m_lState, -1, "name");
   lua_remove(m_lState, -2);
   sprintf(sFunctionName,"Use%s",lua_tostring(m_lState, -1));
   lua_pushobject(m_lState, pTarget);
   lua_getfield(m_lState, -1, "type");
   lua_getfield(m_lState, -1, "name");
   lua_remove(m_lState, -2);
   sprintf(sFunctionName,"%sWith%s",sFunctionName,lua_tostring(m_lState,-1));
   lua_pop(m_lState, 4);
   lua_getglobal(m_lState,sFunctionName); // obj1  obj2  func
   // Pushes a character and two items
   lua_pushobject(m_lState, pUser);
   lua_pushobject(m_lState, pSource);
   lua_pushobject(m_lState, pTarget);

   // Calls the lua function
   lua_call(m_lState,3,0);
}
int lua_pushvarg(lua_State*L, char* format,va_list* argptr)
{
   int n = 0;
   while( *format != '\0' )
   {
      n++;
      switch (*format)
      {
         case 'd':
         case 'i': // number or integer
            lua_pushnumber(L, va_arg(*argptr, int) );
            break;
         case 'b':  //boolean
            lua_pushboolean(L, va_arg(*argptr, int) );
            break;
         case 'c':  //character
            lua_pushboolean(L, va_arg(*argptr, int) );
            break;
         case 's':
            lua_pushstring(L, va_arg(*argptr, char*));
            break;
         default:
            lua_pushlightuserdata(L, va_arg(*argptr, void*) );
            break;
      }
      *format++;
   }
   return n;
}
const char* lua_engine::getobjectstring(lua_obj* loObj, const char* sVar)
{
   lua_pushobject(m_lState, loObj);
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
          sprintf(buffer,"");
          bI=0;
          if(sVar[i]=='\0')
              endloop=true;
      }
   }
}
int lua_engine::getobjectnumber(lua_obj* loObj, const char* sVar)
{
   lua_pushobject(m_lState, loObj);
   getluavar(sVar);
   return lua_tonumber(m_lState, -1);
}
int lua_engine::getobjectboolean(lua_obj* loObj, const char* sVar)
{
   lua_pushobject(m_lState, loObj);
   getluavar(sVar);
   return lua_toboolean(m_lState, -1);
}
void* lua_engine::getobjectpointer(lua_obj* loObj, const char* sVar)
{
   lua_pushobject(m_lState, loObj);
   getluavar(sVar);
   return (void*)lua_topointer(m_lState, -1);
}
void lua_engine::CreateItemType(const char* sName, int nId)
{
   CallLuaMethod("itemtype","new","sd",sName,nId);
}



int lib_RegisterObject(lua_State* L)
{
   lua_engine::Get()->RegisterObject();
   return 0;
}
void lua_pushobject(lua_State* L, lua_obj* loObj)
{
   lua_pushlightuserdata(L, &loObj->key);
   lua_gettable(L, LUA_REGISTRYINDEX);
}
int checkmystack(lua_State* L)
{
   int i;
   int top = lua_gettop(L);
   printf("-----------\n");
   for (i = 1; i<=top; i++) {
      int t = lua_type(L, i);
      printf("#%d [#%d]   ",i, - (top - i + 1));
      switch(t) {
         case LUA_TSTRING:
            printf("String: '%s'", lua_tostring(L, i));
            break;
         case LUA_TBOOLEAN:
            printf("Bool: %s",lua_toboolean(L, i) ? "true" : "false");
            break;
         case LUA_TNUMBER:
            printf("Number: %g",lua_tonumber(L, i));
            break;
         default:
            printf("Unknown <%s>",lua_typename(L, t));
            break;
      }
      printf(" [%d]\n", lua_topointer(L, i));
   }
   return 0;
}
