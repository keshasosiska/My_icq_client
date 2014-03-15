#pragma once

#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <process.h>

class TUser
{
public:
	SOCKET socket;
	TUser *next;

	bool isLoggedIn;
	int id;

	TUser(SOCKET socket);
	~TUser() {};

	void Print();
};


class TUsers
{
public:
	int count;
	TUser *head;
public:
	TUsers();
	void Add(SOCKET user_socket);	// to end
	void Del(SOCKET user_socket);
	void SendAllFriendsTo(SOCKET sock, int id);
	void SendMSGtoID(int id_sender, int id_rec, char *msg);
	void SetID(SOCKET sock, int id);

	void Print();
};
