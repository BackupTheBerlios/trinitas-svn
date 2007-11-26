/** A Class to load and manage loaded Plugins
 * Copyright 2007 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 *
 * @autor   Paradoxon
 * @date    26.11.2007
 * @version 0.1
 */
#include <iostream>
#include "PluginLoader.h"
#include "TrinitasPlugin.h"



/** Construcktor for the PluginLoader later maby we should rename
 * this to PluginManaer
 */
PluginLoader::PluginLoader(void)
{
    //inita the vector wich hold all loaded Plugins
}


void PluginLoader::Load(char *path)
{
    //check if the String is a existing path
    // run through all files test them if they are plugins
    // maby use a protected tool method...
}

TrinitasPlugin* PluginLoader::GetByID(long pluginId)
{
    //need to implement
    return NULL;
}

 TrinitasPlugin* PluginLoader::GetByName(char* pluginName)
 {
    //need to implement
     return NULL;
 }
