/** A First Plugin to test our Addonsystem
 * Copyright 2007 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 *
 * @autor   Paradoxon
 * @date    26.11.2007
 * @version 0.1
 */

#include <iostream>
#include "TrinitasPlugin.h"
#include "FirstPlugin.h"
 //export so that our programm can load it
 extern "C" TrinitasPlugin* load(long id) {
    return new TrinitasPlugin(id);
}

 //export so that our programm delete it
extern "C" void unload(TrinitasPlugin* p) {
    delete p;
}


FirstPlugin::FirstPlugin(long _id):TrinitasPlugin(_id)
{}

char* FirstPlugin::GetName()
{
    return "FirstPlugin";
}
long FirstPlugin::GetID()
{
    return id;
}

void FirstPlugin::Do()
{
    std::cout << "Jo ich hab was im Plugin gemacht" << '\n';
}

