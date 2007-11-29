/*
 * Copyright 2007 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 */
#ifndef PLUGIN_LOADER_H
#define PLUGIN_LOADER_H
#include "TrinitasPlugin.h"

 class PluginLoader {
     public:
                        PluginLoader(void);
        void            Load(char *path);
        TrinitasPlugin* GetByID(long pluginID);
        TrinitasPlugin* GetByName(char *name);
         /*later we add also a Method wich returns
         *of course the List of loaded Plugins
         */
    protected:
    private:
        TrinitasPlugin* LoadPlugin(char *file);
        long            mLastPluginID;
 };
#endif
