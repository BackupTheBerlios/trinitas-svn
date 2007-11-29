/*
 * Copyright 2007 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 */

#ifndef FIRST_PLUGIN_H
#define FIRST_PLUGIN_H

/* to make the code portable we need
 * to handle the different export ways of exporting
 * symbols, we doing this with this define block
 * maby later we should include this as a makro
 * in our TrinitasDefs
 */
#if defined (__GNUC__) && defined(__unix__)
    #define PRINT_API __attribute__ ((__visibility__("default")))
#elif defined (WIN32)
    #ifdef BUILDING_DLL
        #define PRINT_API __declspec(dllexport)
    #else
        #define PRINT_API __declspec(dllimport)
    #endif
#else
    #define PRINT_API
#endif

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

//using exptern to give an "entrypoint" for the PluginLoader
//extern "C" PRINT_API TrinitasPlugin* getPlugin(long id);


#endif
