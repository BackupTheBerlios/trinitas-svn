class lua_event
{
public:
   const char* m_sFunction;
   time_t m_timeStamp;
   va_list args;
};