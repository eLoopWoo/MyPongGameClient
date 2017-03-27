#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib") //Required for WinSock
#include <WinSock2.h> //For win sockets
#include <string> //For std::string
#include <iostream> //For std::cout, std::endl, std::cin.getline

enum Packet
{
	P_ChatMessage,
	P_Test,
	P_moveUP1,
	P_moveDOWN1,
	P_moveUP2,
	P_moveDOWN2,
	P_move
};

class Client
{
public: //Public functions
	Client(std::string IP, int PORT);
	bool Connect();

	bool SendString(std::string & _string);
	bool CloseConnection();

	bool SendMoveDOWN1();
	bool SendMoveUP1();

	bool SendMoveDOWN2();
	bool SendMoveUP2();

	float player_y1 = 250;
	float player_y2 = 250;
	float ball_y = 300;
	float ball_x = 300;

	int player1_score = 0;
	int player2_score = 0;
	void setIP(std::string IP, int PORT);


private: //Private functions
	bool ProcessPacket(Packet _packettype);
	static void ClientThread();
	//Sending Funcs
	bool sendall(char * data, int totalbytes);
	bool Sendint32_t(int32_t _int32_t);
	bool SendPacketType(Packet _packettype);


	//Getting Funcs
	bool recvall(char * data, int totalbytes);
	bool Getint32_t(int32_t & _int32_t);
	bool GetPacketType(Packet & _packettype);
	bool GetString(std::string & _string);

	bool GetMove(float *_x);

	//Move Funcs






private:
	SOCKET Connection;//This client's connection to the server
	SOCKADDR_IN addr; //Address to be binded to our Connection socket
	int sizeofaddr = sizeof(addr); //Need sizeofaddr for the connect function
};

static Client * clientptr; //This client ptr is necessary so that the ClientThread method can access the Client instance/methods. Since the ClientThread method is static, this is the simplest workaround I could think of since there will only be one instance of the client.