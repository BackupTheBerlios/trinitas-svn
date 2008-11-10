#include "MasterServer.h"
#include "RakPeerInterface.h"
#include "BitStream.h"
#include "RakNetworkFactory.h"
#include "MessageIdentifiers.h"
#include "StringCompressor.h"
#include "GetTime.h"
#include "RakNetStatistics.h"

#include <iostream>
// Uncomment this define for debugging printfs
#define _SHOW_MASTER_SERVER_PRINTF
#ifdef _SHOW_MASTER_SERVER_PRINTF
#include <cstdio>
#endif
using namespace std;

MasterServer::MasterServer(){
    running = false;
    initialized = false;
    rakPeer = RakNetworkFactory::GetRakPeerInterface();
    //for the first Test we just allow 32 Servers to connect ;-) for Beta test and so on this should be enought
    /**@todo later set Maxmum Incoming Connections much higher like maybe 256   */
    rakPeer->SetMaximumIncomingConnections(32);
    //use port 7000 just becaus my router can open this port ;-) using pass empty string for using INADDR_ANY
    SocketDescriptor socketDescriptor(7000,0);
    if (rakPeer->Startup(32, 10, &socketDescriptor, 1 )){
        printf("--== MasterServer started ==--\nlistening on  port %d\n",socketDescriptor.port);
        //yes we are up and running so the reciver loop shoudl also run
        running = true;
    }
    else
        /**@todo shutdown the Server because we cant start rakPeer   */
        printf("COUlD NOT START SERVER");
    //we use this insatnace for a Lightwight databaseServer
    rakPeer->AttachPlugin(&databaseServer);
    printf("attachedPlugin\n");

    DataStructures::Table *table;
    //Allow remote row updates?
    bool allowRemoteUpdate  = true;
    //Allow remote table queries?
    bool allowRemoteQuery   = true;
    //Allow remote row removal
    bool allowRemoteRemove  = true;
    //remote table query password - empty for none
    char queryPassword[_SIMPLE_DATABASE_PASSWORD_LENGTH]    = "";
    //remote update password - empty for none
    char updatePassword[_SIMPLE_DATABASE_PASSWORD_LENGTH]   = "";
    //remote table query password - empty for none
    char removePassword[_SIMPLE_DATABASE_PASSWORD_LENGTH]   = "";
    //Only allow one row per uploading IP?
    bool oneRowPerSystemAddress = true;
    //Only allow updates on rows created by that system?
    bool onlyUpdateOwnRows      = true;
    //Remove row if can't ping system?
    bool removeRowOnPingFailure = true;
    //Remove row on system disconnect?
    bool removeRowOnDisconnect  = true;
    //Autogenerate row ids?
    bool autogenerateRowIDs     = true;
	table=databaseServer.AddTable("TrinitasServer", allowRemoteUpdate, allowRemoteQuery, allowRemoteRemove, queryPassword, updatePassword, removePassword, oneRowPerSystemAddress, onlyUpdateOwnRows, removeRowOnPingFailure, removeRowOnDisconnect, autogenerateRowIDs);
    printf("AddTable\n");

	if (table){

    }
    else
     /**@todo real error handling*/
        printf("Table creation failed.  Possibly already exists.\n");
    //set up stdin for blocking free input
    #ifndef WIN32
    if (!Initialize()){
        cout << "You must be a human to use this program.\n";
    }
    #endif
}

MasterServer::~MasterServer(){
    //shut down the Server
    rakPeer->Shutdown(100,0);
    running = false;
	RakNetworkFactory::DestroyRakPeerInterface(rakPeer);
    //restore normal behavior of stdin
    #ifndef WIN32
    Finalize();
    #endif
}

void MasterServer::Run(){
    Packet *p;
    printf("Run\n");
	while (running){
        p=rakPeer->Receive();
		while (p) {
			if (p->data[0]==ID_DISCONNECTION_NOTIFICATION)
				printf("ID_DISCONNECTION_NOTIFICATION\n");
			else if (p->data[0]==ID_CONNECTION_LOST)
				printf("ID_CONNECTION_LOST\n");
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
			{
				char str[256];
				printf("Incoming table:\n");
				DataStructures::Table table;
				if (TableSerializer::DeserializeTable(p->data+sizeof(MessageID), p->length-sizeof(MessageID), &table))
				{
					DataStructures::Page<unsigned, DataStructures::Table::Row*, _TABLE_BPLUS_TREE_ORDER> *cur = table.GetListHead();
					unsigned i;

					printf("Columns:\n");
					for (i=0; i < table.GetColumns().Size(); i++)
					{
						printf("%i. %s : ", i+1, table.GetColumns()[i].columnName);
						if (table.GetColumns()[i].columnType==DataStructures::Table::BINARY)
							printf("BINARY");
						else if (table.GetColumns()[i].columnType==DataStructures::Table::NUMERIC)
							printf("NUMERIC");
						else
							printf("STRING");
						printf("\n");
					}
					if (cur)
						printf("Rows:\n");
					else
						printf("Table has no rows.\n");
					while (cur)
					{
						for (i=0; i < (unsigned)cur->size; i++)
						{
							table.PrintRow(str, 256, ',', true, cur->data[i]);
							printf("RowID %i: %s\n", cur->keys[i], str );
						}
						cur=cur->next;
					}
				}
				else
					printf("Deserialization of table failed.\n");
			}
			BasicConsole();
			rakPeer->DeallocatePacket(p);
			p=rakPeer->Receive();
		}
        RakSleep(30);
	}

}


void MasterServer::BasicConsole(){

    #ifdef WIN32
    if (iskeypressed( 500 ))
    #endif
    #ifdef WIN32
    if (kbhit())
    #endif
    {
        char ch = cin.get();
        if (ch=='e')
            //tell the main loop to stop
            running =false;
    }
}


#ifndef WIN32
bool MasterServer::Initialize(){
 if (!initialized)
    {
    initialized = (bool)isatty( STDIN_FILENO );
    if (initialized)
      initialized = (0 == tcgetattr( STDIN_FILENO, &initial_settings ));
    if (initialized)
      std::cin.sync_with_stdio();
    }
  return initialized;
}

void  MasterServer::Finalize(){
    if (initialized)
        tcsetattr( STDIN_FILENO, TCSANOW, &initial_settings );
}

bool  MasterServer::Linebuffered( bool on){
    struct termios settings;
    if (!initialized)
        return false;

    if (tcgetattr( STDIN_FILENO, &settings ))
        return false;

    if (on)
        settings.c_lflag |= ICANON;
    else
        settings.c_lflag &= ~(ICANON);

    if (tcsetattr( STDIN_FILENO, TCSANOW, &settings ))
        return false;

    if (on)
        setlinebuf( stdin );
    else
        setbuf( stdin, NULL );

  return true;
}

bool  MasterServer::Echo( bool on ){
    struct termios settings;
    if (!initialized)
        return false;

    if (tcgetattr( STDIN_FILENO, &settings ))
        return false;

    if (on)
        settings.c_lflag |= ECHO;
    else
        settings.c_lflag &= ~(ECHO);
    return 0 == tcsetattr( STDIN_FILENO, TCSANOW, &settings );
}

bool  MasterServer::Iskeypressed( unsigned timeout_ms ){
    if (!initialized) return false;

    struct pollfd pls[ 1 ];
    pls[ 0 ].fd     = STDIN_FILENO;
    pls[ 0 ].events = POLLIN | POLLPRI;
    return poll( pls, 1, timeout_ms ) > 0;
}

int main(){
    MasterServer    *masterServer = new MasterServer();
    masterServer->Run();
    delete masterServer;
}
#endif
