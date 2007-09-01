// Headers für Raknet
#include <PacketEnumerations.h>
#include <RakNetworkFactory.h>
#include <NetworkTypes.h>
#include <RakServerInterface.h>
#include <Bitstream.h>

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <conio.h>
#include <vector>

const unsigned char PACKET_ID_LINE = 100; //Daa ist die Standard id die ich festgelegt habe das diese von mir command
int serverid = 100; //ab 100 werden ids für die User vergeben
int numuser; //Anzahl der User auf dem Server

struct playerinfo_struct{ //struct für die Relevanten informationen der User
    int id;
    std::string playername;
};

struct koordinaten_struct{ //struct für die Koordinaten der User
    int id;
    int x;
    int y;
};

std::vector<playerinfo_struct> playerinfo;
std::vector<koordinaten_struct> koordinaten;

void SendPlayerID(RakServerInterface * server, PlayerID client, int command, int id)
{
    BitStream dataStream;

    dataStream.Write(PACKET_ID_LINE);
    dataStream.Write(command);
    dataStream.Write(id);
    //printf("IP: %i, Port: %i",clientToExclude.binaryAddress,clientToExclude.port);

    server->Send(&dataStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, client, false, false);
}

void SendCoords(RakServerInterface * server,PlayerID clientToExclude){
    BitStream dataStream;

    dataStream.Write(PACKET_ID_LINE);
    dataStream.Write(4); //Koordinaten aller User werden gesendet
    dataStream.Write(koordinaten.size()); //Wieviele Koordinaten

    for(int a=0; a<koordinaten.size(); a++){
        dataStream.Write(koordinaten[a].id);
        dataStream.Write(koordinaten[a].x);
        dataStream.Write(koordinaten[a].y);

        for(int b=0; b<playerinfo.size(); b++){
            if(playerinfo[b].id==koordinaten[a].id){
                dataStream.Write(playerinfo[b].playername.length());
                dataStream.Write(const_cast<char *>(playerinfo[b].playername.c_str()),playerinfo[b].playername.length());

                printf("Es wurde gesendet: id %i x %i y %i name: %s\n",koordinaten[a].id,koordinaten[a].x,koordinaten[a].y,playerinfo[b].playername.c_str());
            }
        }


    }

    server->Send(&dataStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_PLAYER_ID, true, true);
}

void HandlePacket(RakServerInterface * server, Packet * p)
{

    unsigned char packetID;

    BitStream dataStream((const char*)p->data, p->length, false);

    dataStream.Read(packetID);

    switch(packetID) {
    case PACKET_ID_LINE:
                int command, playerid;
                int x, y;

                dataStream.Read(command);
                printf("Packet id: %i, Command: %i\n",packetID,command);
                switch(command){
                    //Namen Empfangen
                    case 2: {
                        int streamLength;
                        dataStream.Read(playerid);
                        dataStream.Read(streamLength);
                        char* playername = new char[streamLength];
                        dataStream.Read(playername, streamLength);
                        playerinfo_struct d0 = {playerid,playername};
                        playerinfo.push_back(d0);
                        printf("hier sollte was stehen: %s %i Spieler ID: %i, Paket ID: %i\n",playername,streamLength);
                    }
                    break;
                    case 3:
                    {
                        int exist = 0;
                        dataStream.Read(playerid);
                        dataStream.Read(x);
                        dataStream.Read(y);

                        if(koordinaten.size()!=0){
                            for(int a=0;a<koordinaten.size();a++){
                                if(koordinaten[a].id==playerid){
                                    koordinaten[a].x=x;
                                    koordinaten[a].y=y;
                                    exist = 1;
                                }
                            }
                        }
                        if(exist==0){
                            koordinaten_struct d0 = {playerid,x,y};
                            koordinaten.push_back(d0);
                        }
                        exist = 0;
                        SendCoords(server,p->playerId);
                    }
                        printf("Koordinaten Empfangen von ID: %i X: %i Y: %i",playerid,x,y);
                    break;
                    case 24:
                        dataStream.Read(playerid);
                        for(int a=0;a<playerinfo.size();a++){
                            if(playerinfo[a].id==playerid){
                                playerinfo.erase(playerinfo.begin()+a);
                            }
                        }
                        for(int a=0;a<koordinaten.size();a++){
                            if(koordinaten[a].id==playerid){
                                koordinaten.erase(koordinaten.begin()+a);
                            }
                        }
                        printf("jemand disconnected\n");
                    break;
                }

        /*int streamLength;
        dataStream.Read(streamLength);
        char* buffer = new char[streamLength];
        dataStream.Read(buffer, streamLength);
        printf("hier sollte was stehen: %s %i Spieler ID: %i, Paket ID: %i\n",buffer,streamLength,p->playerId:int,packetID);
        SendLineToClients(server, p->playerId, x1, y1, x2, y2);*/
        //SendPlayerID(server, p->playerId, 1, 2);
    break;
    case ID_RECEIVED_STATIC_DATA:
        SendPlayerID(server, p->playerId, 1, serverid);
        serverid += 1;
        printf("geschickt id");
    break;
    case 21: //Vermutlich der Ping Timeout

    break;
    default:
        printf("Unhandled packet (not a problem): %i\n", int(packetID));
    }
}

int main()
{
    printf("##############################\n"\
           "#                            #\n"\
           "# Raknet Uebung fuer Trinita #\n"\
           "#           von Feuer        #\n"\
           "#                            #\n"\
           "##############################\n\n\n");

    RakServerInterface * server = RakNetworkFactory::GetRakServerInterface();
    Packet * packet = NULL;

    int port = 10000;

    if(server->Start(32, 0, 0, port)) {
        printf("Server started successfully.\n");
        printf("Server is now listening on port %i.\n\n", port);
        printf("Press a key to close server.\n");
    }
    else {
        printf("There was an error starting the server.");
        system("pause");

        return 0;
    }

    while(kbhit() == false) {
        Sleep(1); //Damit es nicht ganz überlastet wird (geht auch ohne Sleep)
        packet = server->Receive();
            if(packet!=0){
        HandlePacket(server,packet);

        server->DeallocatePacket(packet);

    }
    }
    server->Disconnect();

    RakNetworkFactory::DestroyRakServerInterface(server);

    printf("Server closed successfully.\n");

    return 0;

}
