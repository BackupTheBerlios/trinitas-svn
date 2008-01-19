#ifndef LUA_OBJ_TYPE
#define LUA_OBJ_TYPE
class lua_obj_type
{
public:
   const char* m_sName;
   lua_obj_type()
   {
      printf("new lot: %i\n",this);
   }
};
#endif
