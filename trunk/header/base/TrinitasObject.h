/*
 * Copyright 2008 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 *
 */
#ifndef Trinitas_Object_H
#define Trinitas_Object_H
class TrinitasObject {
public:
    void            TrinitasObject(void);
    void            TrinitasObject(unsigned short typ);
    bool            UseWith(TrinitasObject &obj);
        //bool shows whether it was successfull or not
    unsigned short  GetTyp();
    unsigned char   GetStatus();
    bool            SetStatus(unsigned char status);
private:
	IAnimatedMesh*           mesh;
    IAnimatedMeshSceneNode*  node;
    btCollisionShape*        physic;

    unsigned char            status;
    unsigned short           typ;
        //Typ of the Object as number eg. 12 could be a normal roman house

};
#endif
