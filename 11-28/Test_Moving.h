#ifndef __TESTMOVING_H__
#define __TESTMOVING_H__

#include <windows.h>
#include "calculatorDST.h"

extern int npcCurPosX, npcCurPosY;
extern unsigned long long NPC_current_Time;
int npc1_state_flag;

void ShowNpcBlock();
void DeleteBlock();
int NPC_moveLeft();
int NPC_moveRight();
int NPC_moveUp();
int NPC_moveDown();
int NpcMoving();
int CheckNPCState();
int NPC1_die();

#endif