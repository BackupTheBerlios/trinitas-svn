template <class T>
class ctVar
{
public:
   T tValue;
   ctVar()
   {
   }
   void Set(T tNewValue)
   {
      tValue = tNewValue;
   }
   T Get()
   {
      return tValue;
   }
};
