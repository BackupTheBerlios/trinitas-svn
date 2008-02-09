/*
 * Copyright 2008 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 *
 */
#ifndef MAP_H
#define MAP_H
class TrinitasObject {
public:
    void            TrinitasObject(void);
    void            TrinitasObject(unsigned short typ);
    bool            UseWith(TrinitasObject &obj);
        //bool shows whether it was successfull or not
    unsigned short  GetTyp();
private:
	IAnimatedMesh*           mesh;
    IAnimatedMeshSceneNode*  node;
    btCollisionShape*        physic;

    unsigned short           typ;
        //Typ of the Object as number eg. 12 could be a normal roman house

};
#endif
