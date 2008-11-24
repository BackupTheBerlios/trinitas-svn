#include "MasterClient.h"
#include "RakPeerInterface.h"
#include "RakNetworkFactory.h"
#include "StringCompressor.h"
#include "GetTime.h"
#include "RakNetStatistics.h"

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
    rakPeer->Connect(serverURL, 7000, 0, 0);
    serverName="Tester";
    description="This is the first MasterClient test";
    joindPlayers=77;
    maxPlayers=0;
    needPassword=false;
    /**@todo chekc somehosw if we are connected... start timer to check after 2 sec if the connection is proper set up ;-)*/

}

MasterClient::~MasterClient()
{
    rakPeer->Shutdown(100,0);
    running = false;
	RakNetworkFactory::DestroyRakPeerInterface(rakPeer);
}

void MasterClient::Run(){
    Packet *p;
    printf("Run\n");
    databaseClient.QueryTable("TrinitasMainServerTable", 0, 0, 0, (DatabaseFilter*) NULL, 0, 0, 0, UNASSIGNED_SYSTEM_ADDRESS, true);
    running=true;
	while (running){
        p=rakPeer->Receive();
		while (p) {
		    if (p->data[0]==ID_DISCONNECTION_NOTIFICATION)
				printf("ID_DISCONNECTION_NOTIFICATION\n");
			else if (p->data[0]==ID_CONNECTION_LOST){
				printf("ID_CONNECTION_LOST\n");
				running=false;
			}
			else if (p->data[0]==ID_NO_FREE_INCOMING_CONNECTIONS)
				printf("ID_NO_FREE_INCOMING_CONNECTIONS\n");
			else if (p->data[0]==ID_NEW_INCOMING_CONNECTION)
				printf("ID_NEW_INCOMING_CONNECTION\n");
			else if (p->data[0]==ID_CONNECTION_REQUEST_ACCEPTED)
				printf("ID_CONNECTION_REQUEST_ACCEPTED\n");
			else if (p->data[0]==ID_CONNECTION_ATTEMPT_FAILED)
				printf("ID_CONNECTION_ATTEMPT_FAILED\n");
			else if (p->data[0]==ID_DATABASE_UNKNOWN_TABLE)
				printf("ID_DATABASE_UNKNOWN_TABLE\n");
			else if (p->data[0]==ID_DATABASE_INCORRECT_PASSWORD)
				printf("ID_DATABASE_INCORRECT_PASSWORD\n");
			else if (p->data[0]==ID_DATABASE_QUERY_REPLY)
				printf("ID_DATABASE_QUERY_REPLY\n");

        }
	}
}



void MasterClient::QuerryTable(){
}

void MasterClient::UpdateTable(){

    unsigned char numCellUpdates    = 5;
    DatabaseCellUpdate cellUpdates[numCellUpdates];
	RowUpdateMode updateMode    = RUM_UPDATE_OR_ADD_ROW;
	unsigned rowId              = 0;
    bool hasRowId               = false;
    //set up the informations we will send to the masterserver
    strcpy(cellUpdates[0].columnName,"Name");
    cellUpdates[0].columnType=DataStructures::Table::STRING;
    cellUpdates[0].cellValue.Set(serverName);
	strcpy(cellUpdates[1].columnName,"Descriptions");
    cellUpdates[1].columnType=DataStructures::Table::STRING;
    cellUpdates[1].cellValue.Set(description);
	strcpy(cellUpdates[2].columnName,"NeedPassword");
    cellUpdates[2].columnType=DataStructures::Table::NUMERIC;
    cellUpdates[2].cellValue.Set(needPassword);
	strcpy(cellUpdates[3].columnName,"JoindedPlayer");
    cellUpdates[3].columnType=DataStructures::Table::NUMERIC;
    cellUpdates[3].cellValue.Set(joindPlayers);
    strcpy(cellUpdates[4].columnName,"MaxsPlayer");
    cellUpdates[4].columnType=DataStructures::Table::NUMERIC;
    cellUpdates[4].cellValue.Set(maxPlayers);
    databaseClient.UpdateRow(tableName, tablePassword, updateMode, hasRowId, rowId, cellUpdates, numCellUpdates, UNASSIGNED_SYSTEM_ADDRESS, true );

}


int main(){
    MasterClient    *masterClient = new MasterClient();
    masterClient->Run();
    delete masterClient;
}
