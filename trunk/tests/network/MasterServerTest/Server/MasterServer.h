#ifndef MASTER_SERVER_H
#define MASTER_SERVER_H


#include "LightweightDatabaseServer.h"
#include "LightweightDatabaseClient.h"
#include "TableSerializer.h"
#include "BitStream.h"
#include "StringCompressor.h"
#include "DS_Table.h"
#include "LightweightDatabaseServer.h"
#include "RakPeerInterface.h"
#include "RakNetworkFactory.h"
#include "RakSleep.h"
#include "MessageIdentifiers.h"

#ifdef WIN32
#include "Kbhit.h"
#else
#include <cstdio>
#include <iostream>
#include <string>

#include <unistd.h>
#include <termios.h>
#include <poll.h>
#endif


class MasterServer
{
public:
	MasterServer();
	~MasterServer();
    void Run();

protected:
    /** Used to give basic control over the Server
        we check for keystrokes and process them
    */
    void BasicConsole();
#ifndef WIN32
	bool Initialize();
	void Finalize();
	bool Linebuffered( bool on = true );
	bool Echo( bool on = true );
	bool Iskeypressed( unsigned timeout_ms = 0 );
#endif



private:
#ifndef WIN32
	static bool initialized = false;
    static struct termios initial_settings;
#endif
	LightweightDatabaseServer   databaseServer;
    RakPeerInterface            *rakPeer;
    bool                        running;
};

#endif
