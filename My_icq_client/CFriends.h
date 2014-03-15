#pragma once

#include <stdio.h>

class CFriend
{
public:
	int id;
	CFriend *next;

	CFriend(int id) {this->id = id; next = NULL; };
};

class CFriends
{
public:
	CFriend *head;

	CFriends() {head = NULL;};
	void Add(int id);
	void Del(int id);
};