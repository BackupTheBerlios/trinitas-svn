/**
 * Copyright 2008 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 *
 * @autor   Paradoxon
 * @date    02.11.2008
 * @version 0.1
 */

#include <iostream>
#include "PluginLoader.h"
#include "TrinitasPlugin.h"

int main() {
    PluginLoader*   pluginTest  = new PluginLoader;
    TrinitasPlugin* tmpPlugin   = NULL;
    /*load all Plugins in the directory where
     *where this programm is located
     */
    pluginTest->Load("Plugins");
    // this dont work for now dont know why
    cout << "GetPluginByName:\n";

    tmpPlugin = pluginTest->GetByName("Client");
    if (tmpPlugin) {
        cout << "GetPluginByName: ";
        tmpPlugin->Do();
    }
    cout << "GetPluginByID:\n ";

    tmpPlugin = pluginTest->GetAt(1);
    if (tmpPlugin) {
        cout << "GetPluginByID: ";
        tmpPlugin->Do();
    }
	return 0;
}
