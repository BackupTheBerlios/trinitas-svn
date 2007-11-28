/*
 * Copyright 2007 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 */
#ifndef TRINITAS_PLUGIN_H
#define TRINITAS_PLUGIN_H
 class TrinitasPlugin {
     public:
                        TrinitasPlugin(long _id){id=_id;};
        virtual char*   GetName(void);
        virtual long    GetID(void);
        virtual void    Do(void);
    protected:
                long    mId;
 };
#endif
