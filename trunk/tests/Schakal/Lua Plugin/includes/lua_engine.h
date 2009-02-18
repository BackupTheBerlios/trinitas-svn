
/*
 * Copyright 2007 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 *
 * @date     14.02.2009
 */





#ifndef LUA_ENGINE_H
#define LUA_ENGINE_H

#include <iostream>
#include <list.h>
#include <windows.h>
#define BUILD_DLL

extern "C"
{
   #include <lua.h>
   #include <lualib.h>
   #include <lauxlib.h>
}

#define DLLEXPORT __declspec(dllexport)


#include "lua_obj.h"
#include "lua_event.h"
#include "TrinitasPlugin.h"


#define glState LuaPlugin::mlPlugin->mlState
#define glPlugin LuaPlugin::mlPlugin


extern "C" class DLLEXPORT LuaPlugin : public TrinitasPlugin
{
public:
    LuaPlugin(long ID);
    virtual ~LuaPlugin();


    static LuaPlugin* mlPlugin;
    char* GetName();
    static LuaPlugin* Get();

    lua_State* mlState;
    list<LuaObj*> mListlo;
    list<LuaObj*>::iterator mListloI;
    list<LuaEvent*> mListlev;
    list<LuaEvent*>::iterator mListlevI;

    clock_t mCurTime;

    virtual void OpenLibrary(void (*fp)(lua_State*));
    virtual void RegisterFunction(const char* sFunction, lua_CFunction fn);
    virtual void SetPanicFunction(lua_CFunction panicf);
    virtual LuaObj* RegisterObject();
    static int lib_RegisterObject(lua_State* L);

    virtual void CallLuaMethod(const char* sLuaClass, const char* sMethod, char* format, ... );
    virtual LuaObj* CreateCharacter(const char* sRace,const char* sLanguage);
    virtual LuaObj* CreateItem(const char* sType);
    virtual void CreateItemType(const char* sName);
    virtual void Use(LuaObj* pUser, LuaObj* pSource, LuaObj* pTarget);

   // Obj->Stack Access Functions
    virtual void* GetObjectPointer(LuaObj* loObj, const char* sVar);
    virtual char  GetObjectBoolean(LuaObj* loObj, const char* sVar);
    virtual int   GetObjectNumber(LuaObj* loObj, const char* sVar);
    virtual char* GetObjectString(LuaObj* loObj, const char* sVar);
    virtual void  GetLuaVar(const char* sVar);

    ///virtual void PushUserdata(void* ud) = 0;
    virtual int PushVarg(char* format, va_list* varg);
    virtual void PushObject(LuaObj* loObj);
    virtual va_list* ToVarg(char* format, ...);
    virtual int CheckStack();

    ///virtual void ShowEventList() = 0;


    // Language functions
    ///virtual void GetLanguage(const char* sShort) = 0;
    virtual void AddWords(const char* sVar, const char* sWords, const char* sShort);
    virtual const char* GetWords(const char* sVar, const char* sShort);

    // Event functions
    virtual void CheckEvents();
    virtual LuaEvent* StartEvent(int difTime);


    virtual void ParseFile(const char* sFile);
    virtual void Do();
    virtual void Test();
    struct Debug
    {
    };



};





#endif

