/*
 * Copyright 2007 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 */
#ifndef TRINITAS_PLUGIN_H
#define TRINITAS_PLUGIN_H
 class TrinitasPlugin {
     public:
                        TrinitasPlugin(long _id){mID = _id;};
        virtual char*   GetName(void)   = 0;
        virtual long    GetID(void)     = 0;
        virtual void    Do(void)        = 0;
    protected:
                long    mID;
 };
#endif
