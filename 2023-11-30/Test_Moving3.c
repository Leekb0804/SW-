#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "Test_Moving3.h"
#include "cursor.h"
#include "map.h"
#include "calculatorDST3.h"
#include "player.h"
#include "define_state.h"
#include "bomb.h"

#define flagTime 600

int npcCurPosX3, npcCurPosY3;
unsigned long long NPC_current_Time3;
extern unsigned long long current_game_time;
extern int npc3_bomb_exist_count = 0;
int npc3_bomb_max = 1;


void ShowNpcBlock3()
{
	SetCurrentCursorPos(npcCurPosX3, npcCurPosY3);
	printf("★");
}

void DeleteBlock3()
{

	SetCurrentCursorPos(npcCurPosX3, npcCurPosY3);
	printf("  ");
}

int NPC_moveLeft3() {

	if (mapModel[cursorY_to_arrY(npcCurPosY3)][cursorX_to_arrX(npcCurPosX3)] == STATE_BOMB_SETTING)
		printf("⊙");
	else
		DeleteBlock3();
	npcCurPosX3 -= 2;
	set_Empty(npcCurPosX3 / 2, npcCurPosY3);
	SetCurrentCursorPos(npcCurPosX3, npcCurPosY3);
	ShowNpcBlock3();
	return 0;

}

int NPC_moveRight3() {

	if (mapModel[cursorY_to_arrY(npcCurPosY3)][cursorX_to_arrX(npcCurPosX3)] == STATE_BOMB_SETTING)
		printf("⊙");
	else
		DeleteBlock3();
	npcCurPosX3 += 2;
	set_Empty(npcCurPosX3 / 2, npcCurPosY3);
	SetCurrentCursorPos(npcCurPosX3, npcCurPosY3);
	ShowNpcBlock3();

	return 0;

}

int NPC_moveUp3() {

	if (mapModel[cursorY_to_arrY(npcCurPosY3)][cursorX_to_arrX(npcCurPosX3)] == STATE_BOMB_SETTING)
		printf("⊙");
	else
		DeleteBlock3();
	npcCurPosY3 -= 1;
	set_Empty(npcCurPosX3 / 2, npcCurPosY3);
	SetCurrentCursorPos(npcCurPosX3, npcCurPosY3);
	ShowNpcBlock3();

	return 0;
}

int NPC_moveDown3() {

	if (mapModel[cursorY_to_arrY(npcCurPosY3)][cursorX_to_arrX(npcCurPosX3)] == STATE_BOMB_SETTING)
		printf("⊙");
	else
		DeleteBlock3();
	npcCurPosY3 += 1;
	set_Empty(npcCurPosX3 / 2, npcCurPosY3);
	SetCurrentCursorPos(npcCurPosX3, npcCurPosY3);
	ShowNpcBlock3();

	return 0;
}


int NpcMoving3()
{
	int preX = 0, preY = 0;
	int npcX, npcY;

	npcX = npcCurPosX3 / 2;
	npcY = npcCurPosY3;

	int kill_Mode = ShortestDistance3(npcX, npcY); // 여기서 one_srt_dist 배열을 만들어줌 (이 배열을 보고 NPC가 움직임)

	int dx = npcX;
	int dy = npcY;

	SetCurrentCursorPos(npcCurPosX3, npcCurPosY3);


	while (1) { //이 while문 안에 있는 clock변수들은 신경쓰지 않아도 됨, 아직 테스트중, 아마 1칸씩 움직여야 하니까 while 지우는 방법도 고려

		preX = dx;
		preY = dy;

		if (one_srt_dist3[dy][dx + 1] == 1) { // NPC 현재위치 기준 one_srt_dist의 오른쪽이 1이라면 (갈수있는길)
			one_srt_dist3[dy][dx] = 0; // 현재 위치의 one_srt_dist를 0으로 초기화 하고
			if (current_game_time - NPC_current_Time3 > flagTime) {
				NPC_current_Time3 = clock();
				NPC_moveRight3(); //오른쪽으로 이동
			}
			dx += 1;
		}
		else if (one_srt_dist3[dy][dx - 1] == 1) {
			one_srt_dist3[dy][dx] = 0;

			if (current_game_time - NPC_current_Time3 > flagTime) {
				NPC_current_Time3 = clock();
				NPC_moveLeft3();
			}
			dx -= 1;
		}
		else if (one_srt_dist3[dy + 1][dx] == 1) {
			one_srt_dist3[dy][dx] = 0;

			if (current_game_time - NPC_current_Time3 > flagTime) {
				NPC_current_Time3 = clock();
				NPC_moveDown3();
			}
			dy += 1;
		}
		else if (one_srt_dist3[dy - 1][dx] == 1) {
			one_srt_dist3[dy][dx] = 0;

			if (current_game_time - NPC_current_Time3 > flagTime) {
				NPC_current_Time3 = clock();
				NPC_moveUp3();
			}
			dy -= 1;
		}

		if (dx == dstX3 && dy == dstY3) { // 목표 위치에 도착하면 mapModel의 상하좌우를 1로 초기화 하고 블럭을 지워줌 (임시 물풍선)

			if (current_game_time - NPC_current_Time3 > flagTime) {
				if (npc3_bomb_exist_count < npc3_bomb_max) {
					npc3_set_bomb();
				}
				NPCmapModel[dstY3][dstX3] = STATE_NPC_WARNING;
				NPC_current_Time3 = clock();
				if (dx < preX) {
					NPC_moveRight3();
				}
				else if (dx > preX) {
					NPC_moveLeft3();
				}
				else if (dy > preY) {
					NPC_moveUp3();
				}
				else if (dy < preY) {
					NPC_moveDown3();
				}
			}
		}
		return 0;
	}
}

int CheckNPCState3()
{
	// 현재 플레이어 좌표의 정보값에 따라 PlayerState 업데이트
	// 업데이트된 PlayerState 값에 맞게 처리

	////////////추가
	if (checkObject_boom(npcCurPosX3, npcCurPosY3) == 1)
	{
		SetCurrentCursorPos(3, HEIGHT + GBOARD_ORIGIN_Y);
		printf("NPC down!\n");
		npc3_state_flag = 1;
		return (1);
	}
	if (checkPlayer_Killed_NPC(npcCurPosX3, npcCurPosY3, PlayerCurPosX, PlayerCurPosY) == 1) {
		SetCurrentCursorPos(3, HEIGHT + GBOARD_ORIGIN_Y);
		printf("Player down    Game Over!\n\n\n");

		return (2);
	}
	return (0);
}

int NPC3_die() {
	SetCurrentCursorPos(npcCurPosX3, npcCurPosY3);
	set_Empty(npcCurPosX3, npcCurPosY3);
	npcCurPosX3 = 0;
	npcCurPosY3 = 0;
}