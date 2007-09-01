#include <irrlicht.h>
#include <PacketEnumerations.h>
#include <RakNetworkFactory.h>
#include <NetworkTypes.h>
#include <RakClientInterface.h>
#include <BitStream.h>

#include <iostream>
#include <windows.h> // for Sleep()
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

const unsigned char PACKET_ID_LINE = 100;

int myid;

std::string name;

int x=100,y=100;

video::IVideoDriver * driver;
gui::IGUIFont* font;


struct koordinaten_struct{
    int x;
    int y;
    std::string playername;
};

std::vector<koordinaten_struct> koordinaten;

class ClientConnection
{
public:

    ClientConnection(char * serverIP, char * portString)
    : client(NULL)
    {
        client = RakNetworkFactory::GetRakClientInterface();

        client->Connect(serverIP, atoi(portString), 0, 0, 0);
    }

    ~ClientConnection()
    {
        BitStream dataStream;
        dataStream.Write(PACKET_ID_LINE);
        dataStream.Write(24);
        dataStream.Write(myid);

        client->Send(&dataStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0);

        client->Disconnect();
        RakNetworkFactory::DestroyRakClientInterface(client);
    }

    void sendCoords(int x, int y){
        BitStream dataStream;

        dataStream.Write(PACKET_ID_LINE);
        dataStream.Write(3); //Koordinaten ändern
        dataStream.Write(myid);
        dataStream.Write(x);
        dataStream.Write(y);

        client->Send(&dataStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0);
    }
    void sendPlayerStuff(void){

        BitStream dataStream;

        dataStream.Write(PACKET_ID_LINE);
        dataStream.Write(2); //Befehl zum Namen Speichern
        dataStream.Write(myid);
        dataStream.Write(name.length());
        dataStream.Write(const_cast<char *>(name.c_str()),name.length());

        client->Send(&dataStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0);
    }

    void drawRectangels(video::IVideoDriver * driver){

    //driver->draw2DRectangle(video::SColor(255,255,255,255),
      //                      core::rect<s32>(x, y, x+50, y+50));

        for(int a = 0; a<koordinaten.size();a++){

            driver->draw2DRectangle(video::SColor(255,255,255,255),
                                core::rect<s32>(koordinaten[a].x, koordinaten[a].y, koordinaten[a].x+50, koordinaten[a].y+50));

            core::stringw str = koordinaten[a].playername.c_str();
            font->draw(str.c_str(),
                    rect<int>(koordinaten[a].x,koordinaten[a].y,koordinaten[a].x+260,koordinaten[a].y+22),
                    video::SColor(255,0,0,0));

                   // printf("Es muesste was kommen Koordinaten: x: %i y: %i name: %s\n",koordinaten[a].x,koordinaten[a].y,koordinaten[a].playername.c_str());
        }
    }

    void ListenForPackets(void){
        Packet * p = client->Receive();

        if(p != NULL) {

        BitStream dataStream((const char*)p->data, p->length, false);
        unsigned char packetID;

        dataStream.Read(packetID);

        printf("da kam was %i\n",packetID);

            switch(packetID) {
            case PACKET_ID_LINE:
                int command;

                dataStream.Read(command);
                switch(command){
                    //ID Empfangen
                    case 1:
                        dataStream.Read(myid);
                        sendPlayerStuff();
                        printf("Command: %i; id: %i",command,myid);
                    break;
                    case 4: //Koordinaten empfangen
                    {
                        int num_coords, serverid, server_x, server_y, playerid, streamLength;
                        koordinaten.clear();

                        dataStream.Read(num_coords);
                        printf("Es kommen Koordinaten Anzahl %i\n",num_coords);

                        for(int a = 0; a<num_coords; a++){
                            dataStream.Read(serverid);
                            //if(serverid!=myid){
                                dataStream.Read(server_x);
                                dataStream.Read(server_y);

                                dataStream.Read(streamLength);
                                char* playername = new char[streamLength-2];
                                dataStream.Read(playername, streamLength);

                                    koordinaten_struct d0 = {server_x,server_y,playername};
                                    koordinaten.push_back(d0);

                                    printf("Es muesste was kommen Koordinaten: x: %i y: %i name: %s\n",server_x,server_y,playername);
                            //}
                        }
                    }
                }
            break;
            }
            client->DeallocatePacket(p);
        }
    }
public:
    RakClientInterface * client;

};

class MyEventReceiver : public IEventReceiver
{
    public:
    MyEventReceiver(ClientConnection *c)
    : myConnection(NULL){
        myConnection = c;
    }

	virtual bool OnEvent(SEvent event)
	{
		/*
		If the key 'W' or 'S' was left up, we get the position of the scene node,
		and modify the Y coordinate a little bit. So if you press 'W', the node
		moves up, and if you press 'S' it moves down.
		*/

		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		{
		    printf("Taste %i\n",event.KeyInput.Key);
			switch(event.KeyInput.Key)
			{
            case KEY_ESCAPE:
                //device->closeDevice();
                return true;
			case KEY_KEY_W:
                    y -= 1;
                    myConnection->sendCoords(x,y);
                return true;
			case KEY_KEY_S:
                    y += 1;
                    myConnection->sendCoords(x,y);
				return true;
            case KEY_KEY_A:
                    x -= 1;
                    myConnection->sendCoords(x,y);
                return true;
			case KEY_KEY_D:
                    x += 1;
                    myConnection->sendCoords(x,y);
				return true;
			}
		}

		return false;
	}
	private:
	ClientConnection * myConnection;
//MyEventCaller eventnet;
};

int main()
{
    printf("##############################\n"\
           "#                            #\n"\
           "# Raknet Uebung fuer Trinita #\n"\
           "#           von Feuer        #\n"\
           "#                            #\n"\
           "##############################\n\n\n");

    printf("Bitte gib deinen Namen ein\n\n");

	std::cin >> name;

    ClientConnection myConnection("127.0.0.1", "10000");

    /*if(myConnection.client->IsConnected()){
        printf("Verbindung ist da");
    }*/

	MyEventReceiver receiver(&myConnection);

	IrrlichtDevice* device = createDevice( video::EDT_SOFTWARE, core::dimension2d<s32>(640, 480),
		16, false, false, false, &receiver);

	driver = device->getVideoDriver();
	font = device->getGUIEnvironment()->getBuiltInFont();

	int lastFPS = -1;
    x = 100; y = 100;
	while(device->run())
	{

		driver->beginScene(true, true, video::SColor(255,0,0,0));

        myConnection.drawRectangels(driver);


		driver->endScene();

        myConnection.ListenForPackets();

		int fps = driver->getFPS();

		if (lastFPS != fps)
		{
			core::stringw tmp(L"Raknet Beispiel - by Feuer [");
			tmp += driver->getName();
			tmp += L"] fps: ";
			tmp += fps;

			device->setWindowCaption(tmp.c_str());
			lastFPS = fps;
		}
	}

    return 0;
}
