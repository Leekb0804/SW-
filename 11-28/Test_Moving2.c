#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "Test_Moving2.h"
#include "cursor.h"
#include "map.h"
#include "calculatorDST.h"
#include "player.h"

#include "bomb.h"

#define flagTime 800

int npcCurPosX2, npcCurPosY2;
unsigned long long NPC_current_Time2;
extern unsigned long long current_game_time;
extern int npc2_bomb_exist_count = 0;
extern int npc2_state_flag;

int npc2_bomb_max = 1;

void ShowNpcBlock2();

void ShowNpcBlock2()
{
	SetCurrentCursorPos(npcCurPosX2, npcCurPosY2);
	printf("★");
}

void DeleteBlock2()
{

	SetCurrentCursorPos(npcCurPosX2, npcCurPosY2);
	printf("  ");
}

int NPC_moveLeft2() {

	if (mapModel[cursorY_to_arrY(npcCurPosY2)][cursorX_to_arrX(npcCurPosX2)] == STATE_BOMB_SETTING)
		printf("⊙");
	else
		DeleteBlock2();
	npcCurPosX2 -= 2;
	set_Empty(npcCurPosX2 / 2, npcCurPosY2);
	SetCurrentCursorPos(npcCurPosX2, npcCurPosY2);
	ShowNpcBlock2();
	return 0;

}

int NPC_moveRight2() {

	if (mapModel[cursorY_to_arrY(npcCurPosY2)][cursorX_to_arrX(npcCurPosX2)] == STATE_BOMB_SETTING)
		printf("⊙");
	else
		DeleteBlock2();
	npcCurPosX2 += 2;
	set_Empty(npcCurPosX2 / 2, npcCurPosY2);
	SetCurrentCursorPos(npcCurPosX2, npcCurPosY2);
	ShowNpcBlock2();

	return 0;

}

int NPC_moveUp2() {

	if (mapModel[cursorY_to_arrY(npcCurPosY2)][cursorX_to_arrX(npcCurPosX2)] == STATE_BOMB_SETTING)
		printf("⊙");
	else
		DeleteBlock2();
	npcCurPosY2 -= 1;
	set_Empty(npcCurPosX2 / 2, npcCurPosY2);
	SetCurrentCursorPos(npcCurPosX2, npcCurPosY2);
	ShowNpcBlock2();

	return 0;
}

int NPC_moveDown2() {

	if (mapModel[cursorY_to_arrY(npcCurPosY2)][cursorX_to_arrX(npcCurPosX2)] == STATE_BOMB_SETTING)
		printf("⊙");
	else
		DeleteBlock2();
	npcCurPosY2 += 1;
	set_Empty(npcCurPosX2 / 2, npcCurPosY2);
	SetCurrentCursorPos(npcCurPosX2, npcCurPosY2);
	ShowNpcBlock2();

	return 0;
}


int NpcMoving2()
{
	int preX = 0, preY = 0;
	int npcX, npcY;

	npcX = npcCurPosX2 / 2;
	npcY = npcCurPosY2;

	int kill_Mode = ShortestDistance(npcX, npcY); // 여기서 one_srt_dist 배열을 만들어줌 (이 배열을 보고 NPC가 움직임)

	int dx = npcX;
	int dy = npcY;

	SetCurrentCursorPos(npcCurPosX2, npcCurPosY2);


	while (1) { //이 while문 안에 있는 clock변수들은 신경쓰지 않아도 됨, 아직 테스트중, 아마 1칸씩 움직여야 하니까 while 지우는 방법도 고려

		preX = dx;
		preY = dy;

		if (one_srt_dist[dy][dx + 1] == 1) { // NPC 현재위치 기준 one_srt_dist의 오른쪽이 1이라면 (갈수있는길)
			one_srt_dist[dy][dx] = 0; // 현재 위치의 one_srt_dist를 0으로 초기화 하고

			if (current_game_time - NPC_current_Time2 > flagTime) {
				NPC_current_Time2 = clock();
				NPC_moveRight2(); //오른쪽으로 이동
			}
			dx += 1;
		}
		else if (one_srt_dist[dy][dx - 1] == 1) {
			one_srt_dist[dy][dx] = 0;

			if (current_game_time - NPC_current_Time2 > flagTime) {
				NPC_current_Time2 = clock();
				NPC_moveLeft2();
			}
			dx -= 1;
		}
		else if (one_srt_dist[dy + 1][dx] == 1) {
			one_srt_dist[dy][dx] = 0;

			if (current_game_time - NPC_current_Time2 > flagTime) {
				NPC_current_Time2 = clock();
				NPC_moveDown2();
			}
			dy += 1;
		}
		else if (one_srt_dist[dy - 1][dx] == 1) {
			one_srt_dist[dy][dx] = 0;

			if (current_game_time - NPC_current_Time2 > flagTime) {
				NPC_current_Time2 = clock();
				NPC_moveUp2();
			}
			dy -= 1;
		}

		if (dx == dstX && dy == dstY && kill_Mode == 0) { // 목표 위치에 도착하면 mapModel의 상하좌우를 1로 초기화 하고 블럭을 지워줌 (임시 물풍선)

			if (current_game_time - NPC_current_Time2 > flagTime) {
				if (npc2_bomb_exist_count < npc2_bomb_max) {
					npc2_set_bomb();
				}
				NPCmapModel[dstY][dstX] = STATE_NPC_WARNING;
				NPC_current_Time2 = clock();
				if (dx < preX) {
					NPC_moveRight2();
				}
				else if (dx > preX) {
					NPC_moveLeft2();
				}
				else if (dy > preY) {
					NPC_moveUp2();
				}
				else if (dy < preY) {
					NPC_moveDown2();
				}
			}
		}
		return 0;
	}
}

int CheckNPCState2()
{
	// 현재 플레이어 좌표의 정보값에 따라 PlayerState 업데이트
	// 업데이트된 PlayerState 값에 맞게 처리

	////////////추가
	if (checkObject_boom(npcCurPosX2, npcCurPosY2) == 1)
	{
		SetCurrentCursorPos(3, HEIGHT + GBOARD_ORIGIN_Y);
		printf("NPC down!\n");
		npc2_state_flag = 1;
		return (1);
	}
	if (checkPlayer_Killed_NPC(npcCurPosX2, npcCurPosY2, PlayerCurPosX, PlayerCurPosY) == 1) {
		SetCurrentCursorPos(3, 16);
		printf("Player down    Game Over!\n\n\n");

		return (2);
	}
	return (0);
}

int NPC2_die() {
	SetCurrentCursorPos(npcCurPosX2, npcCurPosY2);
	set_Empty(npcCurPosX2, npcCurPosY2);
}