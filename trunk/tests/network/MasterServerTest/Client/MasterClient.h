// TOPOLOGY
// Connect to master server
// Stay connected
// When an information query comes in, parse it and write out to a bitstream.

#ifndef MASTER_CLIENT_H
#define MASTER_CLIENT_H

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

/// \ingroup MasterServer
/// \brief implements the master client
class MasterClient : public MasterCommon
{
public:
	MasterClient();
	~MasterClient();
    Run();

protected:
    QuerryTable();
    UpdateTable();


private:
    RakPeerInterface *rakPeer;
	LightweightDatabaseClient databaseClient;
};

#endif
