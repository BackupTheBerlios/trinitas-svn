// TOPOLOGY
// Connect to master server
// Stay connected
// When an information query comes in, parse it and write out to a bitstream.

#ifndef MASTER_CLIENT_H
#define MASTER_CLIENT_H

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

#include "../MasterGlobals.h"

/// @ingroup MasterServer
/// @brief implements the master client wich would be in the "real game" the server


class MasterClient {
public:
	MasterClient();
	~MasterClient();
    void    Run();

protected:
    /**reads the config file*/
    bool    ReadConfig();
    void    QuerryTable();
    void    UpdateTable();


private:
    RakPeerInterface            *rakPeer;
	LightweightDatabaseClient   databaseClient;
	bool                        running;
	char*                       serverName;
    char*                       description;
    bool                        needPassword;
    int                         joindPlayers;
    int                         maxPlayers;

};

#endif
