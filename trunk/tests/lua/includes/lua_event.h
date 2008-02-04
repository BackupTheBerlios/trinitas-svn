struct lua_event_usewith
{
   static const int type = 1;
   lua_obj* pUser;
   lua_obj* pSource;
   lua_obj* pTarget;
};


class lua_event
{
public:
   clock_t m_timeStamp;
   int m_Time;
   void* m_pData; // zB = (lua_event_usewith*)
   int type;
};

void execute_lua_event(lua_State* L, lua_event* myEvent);
