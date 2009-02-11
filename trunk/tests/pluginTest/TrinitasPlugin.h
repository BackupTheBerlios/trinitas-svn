/*
 * Copyright 2007 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 */
#ifndef TRINITAS_PLUGIN_H
#define TRINITAS_PLUGIN_H



 class TrinitasPlugin {
     public:
        void            SetID(int _id){mID = _id;};
        virtual char*   GetName(void)   = 0;
        int             GetID(void) { return mID;}
        virtual void*   Do(void)        = 0;
        virtual void    Close(void)     = 0;
        virtual void    Test(void)      = 0;
    protected:
                 int    mID;
 };



#endif
