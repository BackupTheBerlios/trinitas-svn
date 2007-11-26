#ifndef FIRST_PLUGIN_H
#define FIRST_PLUGIN_H
#include "TrinitasPlugin.h"


 class FirstPlugin : TrinitasPlugin {
                        FirstPlugin(long _id);
     public:
        virtual char*   GetName(void);
        virtual long    GetID(void);
        virtual void    Do(void);
    protected:
    private:
 };
#endif
