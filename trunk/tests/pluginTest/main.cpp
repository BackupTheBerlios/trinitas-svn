/**
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

int main()
{
    PluginLoader*   pluginTest  = new PluginLoader;
    TrinitasPlugin* tmpPlugin   = NULL;
    /*load all Plugins in the directory where
     *where this programm is located
     */
    pluginTest->Load(".");
    //
    tmpPlugin = pluginTest->GetByName("FirstPlugin");
    tmpPlugin->Do();
	std::cout << "Hello world!" << std::endl;
	return 0;
}
