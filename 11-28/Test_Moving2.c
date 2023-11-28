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
	printf("��");
}

void DeleteBlock2()
{

	SetCurrentCursorPos(npcCurPosX2, npcCurPosY2);
	printf("  ");
}

int NPC_moveLeft2() {

	if (mapModel[cursorY_to_arrY(npcCurPosY2)][cursorX_to_arrX(npcCurPosX2)] == STATE_BOMB_SETTING)
		printf("��");
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
		printf("��");
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
		printf("��");
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
		printf("��");
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

	int kill_Mode = ShortestDistance(npcX, npcY); // ���⼭ one_srt_dist �迭�� ������� (�� �迭�� ���� NPC�� ������)

	int dx = npcX;
	int dy = npcY;

	SetCurrentCursorPos(npcCurPosX2, npcCurPosY2);


	while (1) { //�� while�� �ȿ� �ִ� clock�������� �Ű澲�� �ʾƵ� ��, ���� �׽�Ʈ��, �Ƹ� 1ĭ�� �������� �ϴϱ� while ����� ����� ���

		preX = dx;
		preY = dy;

		if (one_srt_dist[dy][dx + 1] == 1) { // NPC ������ġ ���� one_srt_dist�� �������� 1�̶�� (�����ִ±�)
			one_srt_dist[dy][dx] = 0; // ���� ��ġ�� one_srt_dist�� 0���� �ʱ�ȭ �ϰ�

			if (current_game_time - NPC_current_Time2 > flagTime) {
				NPC_current_Time2 = clock();
				NPC_moveRight2(); //���������� �̵�
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

		if (dx == dstX && dy == dstY && kill_Mode == 0) { // ��ǥ ��ġ�� �����ϸ� mapModel�� �����¿츦 1�� �ʱ�ȭ �ϰ� ���� ������ (�ӽ� ��ǳ��)

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
	// ���� �÷��̾� ��ǥ�� �������� ���� PlayerState ������Ʈ
	// ������Ʈ�� PlayerState ���� �°� ó��

	////////////�߰�
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