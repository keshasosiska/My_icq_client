#pragma once

#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include "CFriends.h"

ref class TClient
{
public:
	int _port;
	char* _server_addr;
	SOCKET my_sock;

	int id;
	bool isOnline;
	
	bool isChatChanged;
	System::String^ chat;

	bool isFriendChanged;
	CFriends *friends;
public:
	TClient(int port, char* server_addr);

	int Login(int id, char* pass);
	bool WatchForData();
	void Logout();

	void Send(const char *OperationType, int id_send, int id_recv, char *msg, const char separator);
	void Send(const char *OperationType, int id, char *pass, const char separator);
};