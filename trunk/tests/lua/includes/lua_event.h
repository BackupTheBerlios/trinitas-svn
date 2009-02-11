

#ifndef LUA_EVENT_H
#define LUA_EVENT_H

#include "lua_engine.h"



class lua_event
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
      lua_obj* pUser;
      lua_obj* pSource;
      lua_obj* pTarget;
      static int lib_Init(lua_State* L);
      static void Init(lua_obj* pUser, lua_obj* pSource, lua_obj* pTarget, int difTime);
   };
   int m_Type;
   clock_t m_timeStamp;
   int m_Time;
   void* m_pData; // zB = (lua_event_usewith*)

   void Execute();
};



#endif
