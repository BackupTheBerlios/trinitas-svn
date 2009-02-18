
/*
 * Copyright 2007 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 *
 * @date     14.02.2009
 */





#ifndef LUA_EVENT_H
#define LUA_EVENT_H

#include "lua_engine.h"



class LuaEvent
{
public:
   struct proto
   {
      static const int type = 0;
      virtual void Run() {}
   };
   struct usewith : public proto
   {
      static const int type = 1;
      void Run();
      LuaObj* mpUser;
      LuaObj* mpSource;
      LuaObj* mpTarget;
      static int lib_Init(lua_State* L);
      static void Init(LuaObj* pUser, LuaObj* pSource, LuaObj* pTarget, int difTime);
   };
   int mType;
   clock_t mTimeStamp;
   int mTime;
   void* mpData; // zB = (lua_event_usewith*)

   void Execute();
};



#endif
