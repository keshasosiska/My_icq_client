#pragma once

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>


class ThreadedServer;
typedef DWORD (ThreadedServer::*LPTHREAD_METHOD)(LPVOID pParam);

// Структура параметров для статической функции.
typedef struct STARTUP_PARAM
{
	ThreadedServer*        pClass;
	LPTHREAD_METHOD    pMethod;
	LPVOID            pParam;
} *LPSTARTUP_PARAM;


class ThreadedServer
{
public:
	ThreadedServer(int port);
	int Start();
private:
	int _port;
	int _nclients;
	
	
	DWORD SexToClient(LPVOID client_socket);
	HANDLE StartThread (LPTHREAD_METHOD pMethod, LPVOID pParam, LPDWORD pdwThreadID = NULL, LPSECURITY_ATTRIBUTES pSecurity = NULL, DWORD dwStackSize = 0, DWORD dwFlags = 0)
	{
		// Создаем структуру и упаковываем данные для статической функции.
		LPSTARTUP_PARAM pStartup = new STARTUP_PARAM;
		pStartup->pClass    = this;
		pStartup->pMethod    = pMethod;
		pStartup->pParam    = pParam;

		// Создаем новый поток.
		return CreateThread(pSecurity, dwStackSize, (LPTHREAD_START_ROUTINE)StartFunc, pStartup, dwFlags, pdwThreadID);
	};
	// Статическая функция, которая запустит метод.
	static DWORD StartFunc (LPSTARTUP_PARAM pStartup)
	{
		// Распаковываем данные в новом потоке.
		// Получаем указатель на класс и на метод класса.
		ThreadedServer* pClass  = pStartup->pClass;
		LPTHREAD_METHOD pMethod = pStartup->pMethod;
		LPVOID pParam           = pStartup->pParam;

		// Запускаем метод класса в новом потоке.
		DWORD dwResult = (pClass->*pMethod)(pParam);

		// Удаляем временные данные и возвращаем код возврата из нового потока.
		delete pStartup;
		return dwResult;
	};
};