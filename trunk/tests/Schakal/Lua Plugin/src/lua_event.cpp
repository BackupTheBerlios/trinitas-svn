
/*
 * Copyright 2007 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 *
 * @autor    David Jablonski, davidjablonski@web.de
 * @date     14.02.2009
 */


#include "lua_engine.h"


void LuaEvent::Execute()
{
   switch(mType) {
   case LuaEvent::usewith::type:
      LuaEvent::usewith* EventData = (LuaEvent::usewith*) mpData;
      EventData->Run();
      break;
   default:
      return;
   }
}


int LuaEvent::usewith::lib_Init(lua_State* L)
{
    LuaObj* mpUser = (LuaObj*)lua_topointer(L,-4);
    LuaObj* mpSource = (LuaObj*)lua_topointer(L,-3);
    LuaObj* mpTarget = (LuaObj*)lua_topointer(L,-2);
    int difTime = (int) lua_tonumber(L,-1);
    lua_pop(L,4);
    LuaEvent::usewith::Init(mpUser,mpSource,mpTarget,difTime);
    return 0;
}


void LuaEvent::usewith::Init(LuaObj* pUser, LuaObj* pSource, LuaObj* pTarget, int difTime)
{

   LuaEvent* newEvent = glPlugin->StartEvent(difTime);
   LuaEvent::usewith* EventData = new LuaEvent::usewith;
   EventData->mpUser = pUser;
   EventData->mpSource = pSource;
   EventData->mpTarget = pTarget;
   newEvent->mpData = EventData;
   newEvent->mType = LuaEvent::usewith::type;
   lua_pushlightuserdata(glState, &newEvent->mTimeStamp);
   glPlugin->PushObject(pSource);
   lua_getfield(glState, -1, "type");
   lua_getfield(glState, -1, "usewith");
   lua_remove(glState,-2);
   lua_pushnumber(glState, pTarget->GetTypeId());
   lua_gettable(glState, -2);
   lua_remove(glState,-2);
   lua_remove(glState,-2);
   lua_settable(glState, LUA_REGISTRYINDEX);
   glPlugin->mListlev.push_back(newEvent);
}


void LuaEvent::usewith::Run()
{
   glPlugin->Use(mpUser,mpSource,mpTarget);
}
