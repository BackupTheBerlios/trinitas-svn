/*
 * Copyright 2007 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 *
 */
#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H#include <vector>#include <string>class MapManager{public:					MapManager(void);	//+++Managment of the Directorys for Loading					AddDirectory(char *directory);					RemoveDirectory(char *directory);					RemoveDirectory(int index);	vector<string>	GetDirectoryList(void);	//---Managment of the Directorys for Loading	//+++Retrive the Map ...	// @todo need replace void*s with a special Trinitasmap class	/*This Method forces MapManager to load the specific Map in a seperate Thread     * It sends the given Message when it´s done to the given MessageReciver	 * if sendProgress is true it sends periodically updates about the loadProgress	 */	void			RequestMap(char *MapName, void *MessageReciver, void *Message, bool sendProgress = true );	// the same like above but is dont make use of a Thread and it blocks until the Map was loaded	void*			RequestMapSync(char *MapName,void *MessageReciver, void *Message, bool sendProgress = true);private:	vector <string>	mDirectoryList;};

#endif