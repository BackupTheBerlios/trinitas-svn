/*
 * Copyright 2008 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 *
 */
#ifndef ENGINE_MANAGER_H
#define ENGINE_MANAGER_H

class EngineManager {
public:
					EngineManager(void);
					  //*gleicher Effekt wie Enginemanager(false)
					EngineManager(bool init);
					  //*bei true werden alle Engines bei initialisiert
					EngineManager(bool irrlicht, bool raknet, bool bullet, bool logic, bool irrklang);
					  //*wie vorheriges, nur für jede Engine einzeln

                    /** falls Engine noch nicht gestartet, jeweilige Engine starten
                    *   außerdem Pointer zurückgeben
                    */
	IrrlichtEngine*	GetGraphicsEngine(void);
	RakNet*			GetNetworkEngine(void);
	Physic*			GetPhysicsEngine(void);
	TrinitasLogic*	GetLogicEngine(void);
	IrrKlang*		GetSoundEngine(void)
                    ~EngineManager(void);
protected:
	status_t		InitIrrlicht(void);
	status_t		InitRakNet(void);
	status_t		InitBulletPhysicsEngine(void);
	status_t		InitLogicEngine(void);
	status_t		InitIrrKlang(void);

	IrrlichtEngine* Irrlicht;
	Raknet*         RakNet;
	Physic*         Physic;
	TrinitasLogic*  TrinitasLogic;
	IrrKlang*       IrrKlang;

};
#endif
