#include "stdafx.h"
#include "TClient.h"

TClient::TClient(int port, char* server_addr)
{
	my_sock = -1;
	_port = port;
	_server_addr = server_addr;
	isOnline = false;
	isChatChanged = false;
	chat = "";
	isFriendChanged = false;
	friends = new CFriends();
};

int TClient::Login(int id, char* pass)
{
	this->id = id;

	char buff[1024];
	// Ўаг 1 инициализаци€ библиотеки Winsock
	if (WSAStartup(0x202,(WSADATA *)&buff[0]))
	{
		//printf("WSAStart error %d\n",WSAGetLastError());
		return -1;
	}
	// Ўаг 2 создание сокета
	// SOCKET my_sock;
	my_sock=socket(AF_INET,SOCK_STREAM,0);
	if (my_sock<0)
	{
		//printf("Socket() error %d\n",WSAGetLastError());
		return -1;
	}
	// Ўаг 3 установка соединени€
	// заполнение структуры sockaddr_in Ц указание адреса и порта сервера
	sockaddr_in dest_addr;
	dest_addr.sin_family=AF_INET;
	dest_addr.sin_port=htons(_port);
	HOSTENT *hst;
	// преобразование IP адреса из символьного в сетевой формат
	if (inet_addr(_server_addr)!=INADDR_NONE)
		dest_addr.sin_addr.s_addr=inet_addr(_server_addr);
	else
		// попытка получить IP адрес по доменному имени сервера
		if (hst=gethostbyname(_server_addr))
			// hst->h_addr_list содержит не массив адресов,
			// а массив указателей на адреса
			((unsigned long *)&dest_addr.sin_addr)[0]=
			((unsigned long **)hst->h_addr_list)[0][0];
		else 
		{
			//printf("Invalid address %s\n",SERVERADDR);
			closesocket(my_sock);
			WSACleanup();
			return -1;
		}
	// адрес сервера получен Ц пытаемс€ установить соединение 
	if (connect(my_sock,(sockaddr *)&dest_addr,sizeof(dest_addr)))
	{
		//printf("Connect error %d\n",WSAGetLastError());
		return -1;
	}
	//printf("—оединение с %s успешно установлено\nType quit for quit\n\n",SERVERADDR);

	// ќтправка серверу сообщени€ о логине
	Send("Login", id, pass, ':');

	return 1;
	/*
	if (int bytes_recv = recv(my_sock,&buff[0],sizeof(buff),0) != SOCKET_ERROR)
	{
		int res_login = strncmp(buff, "Login:OK", strlen("Login:OK"));
	}
	*/
};

bool TClient::WatchForData()
{
	char buf[1024];
	memset(buf,'\0',1024);

	if (int bytes_recv = recv(my_sock,&buf[0],sizeof(buf),0) > 0)
	{
		char * str1 = strtok(buf,":;\0");
		while (str1 != NULL)
		{
			if (strcmp(str1, "Login") == 0)
			{
				char* str_ok = strtok(NULL,":;\0");
				if (strcmp(str_ok, "OK") == 0) isOnline = true;
				else isOnline = false;
			}
			if (strcmp(str1, "Logout") == 0)
			{
				char* str_id = strtok(NULL,":;\0");
				friends->Del(atoi(str_id));
				isFriendChanged = true;				
			}
			if (strcmp(str1, "Friend") == 0)
			{
				char* str2 = strtok(NULL,":;\0");
				char* str3 = strtok(NULL,":;\0");
				if (strcmp(str2, "Add") == 0)
				{
					// ƒобавл€ем в онлайн str3.toInt
					friends->Add(atoi(str3));
					isFriendChanged = true;
				}
				if (strcmp(str2, "Del") == 0)
				{
					// ”дал€ем из онлайна str3.toInt
					friends->Del(atoi(str3));
					isFriendChanged = true;
				}
			}
			if (strcmp(str1, "Message") == 0)
			{
				isChatChanged = true;
				// Message:<id_from>:<text>
				char* str_id = strtok(NULL,":;\0"); //int str_id = atoi(str_id);
				char* msg = strtok(NULL,":;\0");
				
				System::String^ s1 = gcnew System::String(str_id);
				System::String^ s2 = gcnew System::String(msg);
				chat += s1+"> "+s2+ "\n";
			}

			str1 = strtok(NULL,":;\0");
		}
	}
	else
		return false;
};
void TClient::Logout()
{
	if (my_sock>0)
	{
		char *str = "Logout;";
		send(my_sock, str, strlen(str),0);
	}
};


void TClient::Send(const char *OperationType, int id_send, int id_recv, char *msg, const char separator)
{
	//Message:<id_send>:<id_recv>:<msg>

	const int len_id = 20; 
	char buf_id_send[len_id]; char *str_id_send = itoa(id_send,buf_id_send,10);
	char buf_id_recv[len_id]; char *str_id_recv = itoa(id_recv,buf_id_recv,10);
	char* str = new char[strlen(OperationType)+strlen(str_id_send)+strlen(str_id_recv)+strlen(msg)+1+3];
	str[0] = '\0';
	strcat(str, OperationType); strcat(str, ":");
	strcat(str, buf_id_send); strcat(str, ":");
	strcat(str, buf_id_recv); strcat(str, ":");
	strcat(str, msg);

	send(my_sock, str, strlen(str),0);
}
void TClient::Send(const char *OperationType, int id, char *pass, const char separator)
{
	const int len_id = 20; char buf_id[len_id]; char *str_id = itoa(id,buf_id,10);
	char* str = new char[strlen(OperationType)+strlen(str_id)+strlen(pass)+1+2];
	str[0] = '\0';
	strcat(str, "Login:");
	strcat(str, str_id);
	strcat(str, ":");
	strcat(str, pass);

	send(my_sock, str, strlen(str),0);
}