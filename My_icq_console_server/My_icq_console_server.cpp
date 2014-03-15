// My_icq_console_server.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include "stdafx.h"
//#include <stdio.h>
//#include <winsock2.h> // Wincosk2.h должен быть раньше windows!
//#include <windows.h>
#include "TServer.h"

#define MY_PORT 1234 // ѕорт, который слушает сервер


int main(int argc, char* argv[])
{
	TServer server(MY_PORT);
	server.Run();
}