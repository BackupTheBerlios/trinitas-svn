/*
 * Copyright 2007 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 */
#ifndef TRINITAS_PLUGIN_H
#define TRINITAS_PLUGIN_H
 class TrinitasPlugin {
     public:
                        TrinitasPlugin(long _id){mID = _id;};
        /*return the Name of the Plugin*/
        virtual char*   GetName(void)   = 0;
        /*return the id wich was handed over during the creation process of the Plugin*/
        virtual long    GetID(void)     = 0;
        /*hand over the execution to the Plugin (should we run thi do in a sepearated thread?s)*/
        virtual void    Do(void)        = 0;
    protected:
                long    mID;
 };
#endif
