// My_icq_console_server.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
//#include <stdio.h>
//#include <winsock2.h> // Wincosk2.h ������ ���� ������ windows!
//#include <windows.h>
#include "TServer.h"

#define MY_PORT 1234 // ����, ������� ������� ������


int main(int argc, char* argv[])
{
	TServer server(MY_PORT);
	server.Run();
}