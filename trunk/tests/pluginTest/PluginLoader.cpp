/** A Class to load and manage loaded Plugins
 * Copyright 2007 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 *
 * @autor   Paradoxon
 * @date    26.11.2007
 * @version 0.1
 */

#ifndef WIN32
    #include <dlfcn.h>
#else
    #include <Windows.h>
#endif

#include <iostream>
#include "PluginLoader.h"
#include "TrinitasPlugin.h"



/** Construcktor for the PluginLoader later maby we should rename
 * this to PluginManaer
 */
PluginLoader::PluginLoader(void) {
    //neet todo init the vector wich hold all loaded Plugins
    //for now we just use a simple Integer to hold the last ID
    // in the future we shall use the Vector Count for generating a ID
    mLastPluginID = 1;
}


void PluginLoader::Load(char *path) {
    //check if the String is a existing path
    // run through all files test them if they are plugins
    // maby use a protected tool method...
}

TrinitasPlugin* PluginLoader::GetByID(long pluginId) {
    //need to implement
    return NULL;
}

 TrinitasPlugin* PluginLoader::GetByName(char* pluginName) {
    //need to implement
     return NULL;
 }

 TrinitasPlugin* PluginLoader::LoadPlugin(char *file) {
    TrinitasPlugin  *loadedPlugin;
    #ifndef WIN32
        void* libraryHandle = dlopen(file, RTLD_LAZY);
        if (libraryHandle != NULL) {
            //using typedef to define a Functiontemplate for the loaded symbols
            typedef TrinitasPlugin* (*pluginFunction)(long id);
            //using the functionvar the Plugin as referrence
            pluginFunction thePlugin;
            thePlugin = (pluginFunction) dlsym(libraryHandle, "getPlugin");
            //call getPlugin with the actual ID
            loadedPlugin = (TrinitasPlugin *) thePlugin(mLastPluginID);
        }
        dlclose(libraryHandle);
    #else // Windwos stuff
        HINSTANCE__* libraryHandle = LoadLibraryA(file);
        if (libraryHandle != NULL)
            //call getPlugin with the actual ID
            loadedPlugin = (TrinitasPlugin*) (GetProcAddress(libraryHandle, "getPlugin"))(mLastPluginID);
        FreeLibrary(libraryHandle);
    #endif
     return loadedPlugin;
 }
