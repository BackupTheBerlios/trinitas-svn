/*
 * Copyright 2007 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 */
#ifndef PLUGIN_LOADER_H
#define PLUGIN_LOADER_H
#include <vector.h>

#include "TrinitasPlugin.h"

 class PluginLoader {
     public:
                            PluginLoader(void);
        void                Load(char *path);
        TrinitasPlugin*     GetAt(long index);
        TrinitasPlugin*     GetByName(char *name);
         /*later we add also a Method wich returns
         *of course the List of loaded Plugins
         */
    protected:
    private:
        TrinitasPlugin*     LoadPlugin(char *file);

        vector<TrinitasPlugin*> *mPlugins;
 };
#endif
