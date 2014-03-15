#include "stdafx.h"
#include "TServer.h"

#define PRINTNUSERS if (nclients) printf("%d user online\n",nclients);else printf("No User on line\n");

TServer::TServer(int port)
{
	this->_port = port;
	users = new TUsers();

	nclients = 0;
};

int TServer::Run()
{
	char buff[1024]; // ����� ��� ��������� ����
	printf("TCP SERVER DEMO\n");
	// ��� 1 ������������� ���������� �������
	// �. �. ������������ �������� ���������� �� ������������
	// �� ���������� ��������� �� ������� �����, ������������� � ��������� 
	// �� ��������� WSADATA.
	// ����� ����� ��������� ���������� ���� ����������, ������, �����
	// ������ ���� �� ����� ������������ �������� (��������� WSADATA
	// �������� 400 ����)
	if (WSAStartup(0x0202,(WSADATA *) &buff[0])) 
	{
		// ������!
		printf("Error WSAStartup %d\n",WSAGetLastError());
		return 1;
	}
	// ��� 2 �������� ������
	SOCKET mysocket;
	// AF_INET ����� ���������
	// SOCK_STREAM ��������� ����� (� ���������� ����������)
	// 0 �� ��������� ���������� TCP ��������
	if ((mysocket=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		// ������!
		printf("Error socket %d\n",WSAGetLastError());
		WSACleanup(); // �������������� ���������� Winsock
		return 1;
	}
	// ��� 3 ���������� ������ � ��������� �������
	sockaddr_in local_addr;
	local_addr.sin_family=AF_INET;
	local_addr.sin_port=htons(_port); // �� �������� � ������� �������!!!
	local_addr.sin_addr.s_addr=0; // ������ ��������� �����������
	// �� ��� ���� IP ������
	// �������� bind ��� ����������
	if (bind(mysocket,(sockaddr *) &local_addr, sizeof(local_addr)))
	{
		// ������
		printf("Error bind %d\n",WSAGetLastError());
		closesocket(mysocket); // ��������� �����!
		WSACleanup();
		return 1;
	}
	// ��� 4 �������� �����������
	// ������ ������� � 0x100
	if (listen(mysocket, 0x100))
	{
		// ������
		printf("Error listen %d\n",WSAGetLastError());
		closesocket(mysocket);
		WSACleanup();
		return 1;
	}
	printf("Waiting..\n");
	// ��� 5 ��������� ��������� �� �������
	SOCKET client_socket; // ����� ��� �������
	sockaddr_in client_addr; // ����� ������� (����������� ��������)
	// ������� accept ���������� �������� ������ ���������
	int client_addr_size=sizeof(client_addr);
	// ���� ���������� �������� �� ����������� �� �������
	while((client_socket=accept(mysocket, (sockaddr *) &client_addr, &client_addr_size)))
	{
		nclients++; // ����������� ������� �������������� ��������
		// �������� �������� ��� �����
		//HOSTENT *hst;
		//hst=gethostbyaddr((char *) &client_addr.sin_addr.s_addr,4,AF_INET);
		// ����� �������� � �������
		//printf("+%s [%s] new connect!\n", (hst)?hst->h_name:"",inet_ntoa(client_addr.sin_addr));
		PRINTNUSERS

		DWORD thID;
		_client_socket = client_socket;
		users->Add(client_socket);
		//printf("---------------");
		/*HandleThread = */CreateThread(NULL, 0, ThreadF, this, 0, &thID);
	}
	return 0;
};

unsigned long TServer::ClientThread()
{
	SOCKET my_sock = _client_socket;
	
	char buff[20*1024];
	memset(buff, '\0', sizeof(buff));

	int bytes_recv = recv(my_sock,&buff[0],sizeof(buff),0);
	while( bytes_recv != SOCKET_ERROR)
	{
		ProcessString(buff, my_sock);

		memset(buff, '\0', sizeof(buff));
		bytes_recv = recv(my_sock,&buff[0],sizeof(buff),0);
	}
	// ���� �� �����, �� ��������� ����� �� ����� �� ������� 
	// ���������� �������� recv ������ � ���������� � �������� ���������
	users->Del(my_sock);
	nclients--; // ��������� ������� �������� ��������
	users->Print();
	// ��������� �����
	closesocket(my_sock);
	return 0;
};

void TServer::ProcessString(char* buf, SOCKET sock)
{
	char * str1 = strtok(buf,":");
	if (strcmp(str1, "Login") == 0)
	{
		char* str_id = strtok(NULL,":"); int int_id = atoi(str_id);
		char* str_pass = strtok(NULL,":\0");
		printf("%s connected with pass %s\n", str_id, str_pass);
		if (ifUserExists(int_id, str_pass)) // �������� ������/������
		{
			this->users->SetID(sock, int_id);
			send(sock,"Login:OK;",strlen("Login:OK;"),0);
			this->users->SendAllFriendsTo(sock, int_id);
		}
		else send(sock,"Login:Fail;",strlen("Login:Fail;"),0);

		users->Print();
	}
	if (strcmp(str1, "Logout") == 0)
	{
		this->users->Del(sock);
		this->users->Print();
	}
	if (strcmp(str1, "Message") == 0)	//Message:<id_send>:<id_rec>:<msg>
	{
		char* str_id_send = strtok(NULL,":"); int int_id_send = atoi(str_id_send);
		char* str_id_rec = strtok(NULL,":"); int int_id_rec = atoi(str_id_rec);
		char* str_msg = strtok(NULL,":\0");
		this->users->SendMSGtoID(int_id_send, int_id_rec, str_msg);
	}
};