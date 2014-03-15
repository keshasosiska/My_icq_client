#pragma once

#include "TUsers.h"

class TServer
{
private:
	TUsers *users;

	int _client_socket;
	static DWORD WINAPI ThreadF(void *arg) {return ((TServer*)arg)->ClientThread();}
	unsigned long ClientThread();

	int _port;
	int nclients;
public:
	TServer(int port);
	int Run();

private:
	void ProcessString(char* buf, SOCKET sock);
	bool ifUserExists(int id, char* pass) {return true;}
};