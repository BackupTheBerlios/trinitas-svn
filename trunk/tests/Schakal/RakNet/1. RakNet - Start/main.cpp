#include <stdio.h>
#include <string.h>

#include <winsock2.h>
#include "RakNetworkFactory.h"
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"

#define MAX_CLIENTS 10
#define SERVER_PORT 80

int main(void)
{
	char str[512];

	RakPeerInterface *peer = RakNetworkFactory::GetRakPeerInterface();
	bool isServer;
	Packet *packet;

	printf("(C) or (S)erver?\n");
	gets(str);

	if ((str[0]=='c')||(str[0]=='C'))
	{
		peer->Startup(1,30,&SocketDescriptor(), 1);
		isServer = false;
	} else {
		peer->Startup(MAX_CLIENTS, 30, &SocketDescriptor(SERVER_PORT,0), 1);
		isServer = true;
	}


	if (isServer)
	{
		printf("Starting the server.\n");
		// We need to let the server accept incoming connections from the clients
		peer->SetMaximumIncomingConnections(MAX_CLIENTS);
	} else {
		printf("Enter server IP or hit enter for 127.0.0.1\n");
		gets(str);
		if (str[0]==0){
			strcpy(str, "127.0.0.1");
		}
		printf("Starting the client.\n");
		peer->Connect(str, SERVER_PORT, 0,0);

	}

	while (1)
	{
		packet=peer->Receive();
		if (packet)
		{
			switch (packet->data[0])
			{
			case ID_REMOTE_DISCONNECTION_NOTIFICATION:
				printf("Another client has disconnected.\n");
				break;
			case ID_REMOTE_CONNECTION_LOST:
				printf("Another client has lost the connection.\n");
				break;
			case ID_REMOTE_NEW_INCOMING_CONNECTION:
				printf("Another client has connected.\n");
				break;
			case ID_CONNECTION_REQUEST_ACCEPTED:
				printf("Our connection request has been accepted.\n");
				break;

			case ID_NEW_INCOMING_CONNECTION:
				printf("A connection is incoming.\n");
				break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				printf("The server is full.\n");
				break;
			case ID_DISCONNECTION_NOTIFICATION:
				if (isServer){
					printf("A client has disconnected.\n");
				} else {
					printf("We have been disconnected.\n");
				}
				break;
			case ID_CONNECTION_LOST:
				if (isServer){
					printf("A client lost the connection.\n");
				} else {
					printf("Connection lost.\n");
				}
				break;
			default:
				printf("Message with identifier %i has arrived.\n", packet->data[0]);
				break;
			}

			peer->DeallocatePacket(packet);
		}
	}


	RakNetworkFactory::DestroyRakPeerInterface(peer);

	return 0;
}



