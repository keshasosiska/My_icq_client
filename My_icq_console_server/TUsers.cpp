#include "stdafx.h"
#include "TUsers.h"

TUser::TUser(SOCKET socket)
{ this->socket = socket; next = NULL; isLoggedIn = false; };
void TUser::Print()
{ 
	if (isLoggedIn)
		printf("(id=%i, sock=%i)", id, socket);
	else
		printf("(id=NaN, sock=%i)", id, socket);
};


TUsers::TUsers()
{ count = 0; head = NULL; };

void TUsers::Add(SOCKET user_socket)	// to end
{
	count++;
	TUser *tmp = head;
	if (head == NULL) 
	{
		head = new TUser(user_socket);
	}
	else
	{
		while (tmp->next!=NULL) tmp = tmp->next;
		tmp->next = new TUser(user_socket);
	}
};
void TUsers::Del(SOCKET user_socket)
{
	int id_del;

	TUser *tmp = head;
	TUser *fordel = NULL;
	if (tmp == NULL) return;
	if (head->socket == user_socket)
	{
		id_del = head->id;
		fordel = head;
		head = head->next;
		fordel->~TUser();
		count--;
	}
	else
	{
		while (tmp->next!=NULL && tmp->next->socket!=user_socket) tmp = tmp->next;
		if (tmp->next == NULL) return;
		fordel = tmp->next;
		tmp->next = tmp->next->next;
		id_del = fordel->id;
		fordel->~TUser();
		count--;
	}

	// отправляем всем что разлогинился
	tmp = head;
	while (tmp!=NULL)
	{
		char str1[20];
		memset(str1, '\0', sizeof(str1));
		sprintf(str1, "Friend:Del:%i;", id_del);
		send(tmp->socket, str1, strlen(str1),0);
		tmp = tmp->next;
	}
};
void TUsers::SendAllFriendsTo(SOCKET sock, int id)
{
	TUser *tmp = head;

	while (tmp!=NULL)
	{
		if (tmp->isLoggedIn && tmp->socket != sock)
		{
			char str1[20], str2[20];
			sprintf(str1,"Friend:Add:%i;",tmp->id);
			sprintf(str2,"Friend:Add:%i;",id);
			send(sock, str1, strlen(str1),0);
			send(tmp->socket, str2, strlen(str2),0);
		}
		tmp = tmp->next;
	}
};
void TUsers::SendMSGtoID(int id_sender, int id_rec, char *msg)
{
	TUser *tmp = head;
	while (tmp!=NULL)
	{
		if (tmp->id == id_rec)
		{
			// Формируем строку
			// Message:<id_send>:<msg>
			char *OperationType = "Message";
			const int len_id = 20; 
			char buf_id_sender[len_id]; char *str_id_sender = itoa(id_sender,buf_id_sender,10);
			
			char* str = new char[strlen(OperationType)+strlen(str_id_sender)+strlen(msg)+1+2];
			str[0] = '\0';
			strcat(str, OperationType); strcat(str, ":");
			strcat(str, str_id_sender); strcat(str, ":");
			strcat(str, msg);

			// Отправляем
			printf("Sending to %i msg: %s\n", id_rec, str);
			send(tmp->socket, str, strlen(str),0);
		}

		tmp = tmp->next;
	}
}
void TUsers::SetID(SOCKET sock, int id)
{
	TUser *tmp = head;
	while (tmp->socket!=sock && tmp!=NULL)	tmp = tmp->next;
	if (tmp == NULL) return;
	tmp->isLoggedIn = true;
	tmp->id = id;
};

void TUsers::Print()
{
	printf("Users : ");

	TUser *tmp = head;
	while (tmp!=NULL)
	{
		tmp->Print();
		printf(" ");
		tmp = tmp->next;
	}
	printf("\n");
};