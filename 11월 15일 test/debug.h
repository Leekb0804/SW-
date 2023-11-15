#include <stdio.h>

#include "cursor.h"
#include "Test_Moving.h"

extern int npcCurPosX;
extern int npcCurPosY;

void print_npc_x_y()
{
	COORD pre = GetCurrentCursorPos();

	SetCurrentCursorPos(6, 20);
	printf("x : %d y : %d\n", npcCurPosX, npcCurPosY);

	SetCursorPos(pre.X, pre.Y);
}


void print_1()
{
	COORD pre = GetCurrentCursorPos();

	SetCurrentCursorPos(6, 22);
	printf("1\n");

	SetCursorPos(pre.X, pre.Y);
}

void print_2()
{
	COORD pre = GetCurrentCursorPos();

	SetCurrentCursorPos(6, 24);
	printf("2\n");

	SetCursorPos(pre.X, pre.Y);
}

void print_3()
{
	COORD pre = GetCurrentCursorPos();

	SetCurrentCursorPos(6, 26);
	printf("3\n");

	SetCursorPos(pre.X, pre.Y);
}