/*
 * Copyright 2007 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 *
 */
#ifndef ENGINE_MANAGER_H
#define ENGINE_MANAGER_H
class EngineManager {public:					EngineManager(void);	IrrlichEngine*	GetIrrlichEngine(void);	RakNet*			GetRakNetEngine(void);	Physik*			GetPhysikEngine(void);	TrinitasLogik*	GetLogikEngine(void);	IrrKlang*		GetSoundEngine(void)protected:	status_t		InitIrrlich(void);	status_t		RakNet(void);	status_t		PhysikEngine(void);	status_t		PhysikEngine(void);	status_t		GetSoundEngine(void);};
#endif