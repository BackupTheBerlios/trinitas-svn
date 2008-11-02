/**The ClientPlugin for Trinitas
 * This is the Plugin the most people will use
 * Copyright 2008 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 *
 * @autor   Paradoxon
 * @date    02.11.2008
 * @version 0.1
 */

#include <iostream>
#include "ClientPlugin.h"


int  main(long id) {
}

ClientPlugin::ClientPlugin(long _id):TrinitasPlugin(_id){
}

char* ClientPlugin::GetName(){
    return "Client";
}

long ClientPlugin::GetID(){
    return mID;
}

void ClientPlugin::Do() {
    std::cout << "Jo ich hab was im Plugin gemacht" << '\n';
}

