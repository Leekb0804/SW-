#ifndef __TESTMOVING_H__
#define __TESTMOVING_H__

#include <windows.h>
#include "calculatorDST.h"

extern int npcCurPosX, npcCurPosY;
extern clock_t NPC_current_Time;


void ShowNpcBlock(); // NPC 아이콘 출력 함수
void DeleteBlock(); // NPC 아이콘 삭제함수
int NPC_moveLeft(); // NPC 좌측 이동
int NPC_moveRight(); // NPC 우측 이동
int NPC_moveUp(); // NPC 상단 이동
int NPC_moveDown(); // NPC 하단 이동
int NpcMoving(clock_t current_game_time); // NPC 이동함수, 여기서 shortestDistance 함수 호출해서 one_srt_dist 배열을 만든다
void SetNpcPos(); // 첫 NPC 위치 설정


#endif
