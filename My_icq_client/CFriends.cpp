#include "stdafx.h"
#include "CFriends.h"

void CFriends::Add(int id)
{
	if (head == NULL) 
	{
		head = new CFriend(id);
		return;
	}

	CFriend *tmp = head;
	while (tmp->next != NULL && tmp->id!=id) tmp = tmp->next;
	if (tmp->id == id) return;

	tmp->next = new CFriend(id);
};

void CFriends::Del(int id)
{
	if (head == NULL) return;
	CFriend *tmp = head;
	if (head->id == id)
	{
		head = head->next;
		tmp->~CFriend();
		return;
	}
	while (tmp->next != NULL && tmp->next->id!=id) tmp = tmp->next;
	if (tmp->next == NULL) return;

	CFriend *fordel = tmp->next;
	tmp->next = fordel->next;
	fordel->~CFriend();
};