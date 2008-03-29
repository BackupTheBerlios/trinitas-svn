/*
 * Copyright 2008 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 *
 */
#ifndef Trinitas_Object_H
#define Trinitas_Object_H

#include "../TrinitasDefs.h"

class TrinitasObject {
public:
    void            TrinitasObject(void);
    void            TrinitasObject(TrinitasObject& obj);
        //copy constructor
    void            TrinitasObject(unsigned short typ);


    bool            UseWith(TrinitasObject& obj);
        //bool shows whether it was successfull or not
    TrinitasObject  operator+ (TrinitasObject& obj);
        //it is called if you add two objects and it calls UseWith


    unsigned short  GetTyp();
    unsigned char   GetStatus();
    bool            SetStatus(unsigned char status);

    void            update();
        //sync. the data of all engines

    void            move(vector3d force);


private:
    vector<IAnimatedMeshSceneNode*>  node;
    vector<btCollisionShape*>        physic;
    vector<soundData>                sound;

    unsigned char            status;
    unsigned short           typ;
        //Typ of the Object as number eg. 12 could be a normal roman house

};
#endif
