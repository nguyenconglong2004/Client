#pragma once
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib,"WS2_32")
class Socket {
public:
	int init_and_connect();
	int send_Event(int type, int x, int y);
	void break_up();
	int data[3] = { 0 };
	Socket();
	~Socket();
private:
	WSADATA wsaData;
	SOCKET connectSocket;
	sockaddr_in address;

};

