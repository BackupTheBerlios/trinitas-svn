#include "lua_engine.h"

// Starts and initializes the engine
void lua_engine::Start()
{
   m_lState=lua_open();
   luaL_openlibs(m_lState);
   m_pSingleton = this;
}

// Stops the engine and releases the memory
void lua_engine::Release()
{
   lua_close(m_lState);
   m_lState = NULL;
   m_listlpot.clear();
   m_listlpo.clear();
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

// Creates a new lua obj type and adds it to our list
lua_obj_type* lua_engine::AddLuaObjType(const char* sName)
{
   lua_obj_type* lpObjType = new lua_obj_type();
   lpObjType->m_sName = sName;
   m_listlpot.push_back(lpObjType);
   return lpObjType;
}

// Searches a lua obj type in the list by his name
lua_obj_type* lua_engine::GetLuaObjType(const char* sName)
{
   if (m_listlpot.empty()==false)
   {
      for(m_listlpot_i=m_listlpot.begin(); m_listlpot_i!=m_listlpot.end(); ++m_listlpot_i)
      {
         if(strcmp((*m_listlpot_i)->m_sName,sName)==0)
         {
            return *m_listlpot_i;
         }
      }
   }
}

// Creates a new object by the name of his type
lua_obj* lua_engine::CreateObject(const char* sName)
{
   lua_obj_type* lpObjType = GetLuaObjType(sName);
   lua_obj* newObject = new lua_obj(lpObjType);
   m_listlpo.push_back(newObject);
   return newObject;
}
lua_obj* lua_engine::CreateObject_meta(const char* sName, const char* mtName)
{
   lua_obj* newObj = (lua_obj*) lua_newuserdata(m_lState, sizeof(lua_obj));
   newObj->m_lptData = new lua_Table;
   newObj->m_lptData->Update();
   luaL_getmetatable(m_lState, mtName);
   lua_setmetatable(m_lState, -2);

   // Pushes the new object onto the registry
   lua_pushstring(m_lState,newObj->TableName());
   lua_pushvalue(m_lState, -2);
   lua_settable( m_lState, LUA_REGISTRYINDEX );

   newObj->m_lptData->InsertValues();
   newObj->AssignObjType(lua_engine::Get()->GetLuaObjType(sName));
   newObj->m_lptData->Update();
   return newObj;
}

lua_obj* lua_engine::CreateCharacter(const char* sName)
{
   lua_obj* newChar = CreateObject_meta(sName, "LuaBook.character");
   lua_getglobal(m_lState,"CreateCharacter");
   lua_getglobal(m_lState, newChar->TableName());
   lua_call(m_lState,1,0);
   return newChar;
}
lua_obj* lua_engine::CreateItem(const char* sName)
{
   return CreateObject_meta(sName, "LuaBook.item");
}


// Calls the Lua function with two objects
void lua_engine::Use(lua_obj* loUser, lua_obj* loSource, lua_obj* loTarget)
{
   char* sFunctionName = new char[60];
   sprintf(sFunctionName,"Use%sWith%s",loSource->m_lpotType->m_sName,loTarget->m_lpotType->m_sName);
   lua_getglobal(m_lState,sFunctionName);


   lua_pushstring(m_lState,loUser->TableName());
   lua_gettable(m_lState, LUA_REGISTRYINDEX);

   lua_getglobal(m_lState,loSource->m_lptData->m_sName);
   lua_getglobal(m_lState,loTarget->m_lptData->m_sName);
   lua_call(m_lState,3,0);
   loSource->CheckType();
   loTarget->CheckType();
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
