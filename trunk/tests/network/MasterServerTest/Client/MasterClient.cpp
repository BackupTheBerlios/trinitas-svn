#include "MasterClient.h"
#include "RakPeerInterface.h"
#include "PacketEnumerations.h"
#include "RakNetworkFactory.h"
#include "StringCompressor.h"
#include "GetTime.h"
#include <cstring>

// Uncomment this define for debugging printfs
#define _SHOW_MASTER_SERVER_PRINTF
#ifdef _SHOW_MASTER_SERVER_PRINTF
#include <cstdio>
#endif

MasterClient::MasterClient(){
    rakPeer = RakNetworkFactory::GetRakPeerInterface();
    SocketDescriptor socketDescriptor(0,0);
    rakPeer->Startup(1, 0, &socketDescriptor, 1);
    rakPeer->AttachPlugin(&databaseClient);
    rakPeer->Connect("paradoxon.servegame.com", 7000, 0, 0);
}

MasterClient::~MasterClient()
{
    rakPeer->Shutdown(100,0);
    running = false;
	RakNetworkFactory::DestroyRakPeerInterface(rakPeer);
}

void MasterServer::Run(){
    Packet *p;
    printf("Run\n");
	while (running){
        p=rakPeer->Receive();
		while (p) {
            DatabaseFilter filter[255];
            unsigned int numFilters=0;
	}
}
