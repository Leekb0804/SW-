#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "Test_Moving.h"
#include "LeeGB_cursor.h"
#include "LeeGB_map.h"
#include "block_model.h"
#include "calculatorDST.h"

int npcCurPosX, npcCurPosY;
clock_t NPC_current_Time;
#define flagTime 1.5

void SetNpcPos() {

	npcCurPosX = 2;
	npcCurPosY = 8;

	SetCurrentCursorPos(npcCurPosX, npcCurPosY);

	ShowNpcBlock();
}

void block_break() {
	

	SetCurrentCursorPos(npcCurPosX + 2, npcCurPosY);
	printf("  ");
	SetCurrentCursorPos(npcCurPosX, npcCurPosY);

	SetCurrentCursorPos(npcCurPosX - 2, npcCurPosY);
	printf("  ");
	SetCurrentCursorPos(npcCurPosX, npcCurPosY);

	SetCurrentCursorPos(npcCurPosX, npcCurPosY + 1);
	printf("  ");
	SetCurrentCursorPos(npcCurPosX, npcCurPosY);

	SetCurrentCursorPos(npcCurPosX, npcCurPosY - 1);
	printf("  ");
	SetCurrentCursorPos(npcCurPosX, npcCurPosY);
}

void ShowDstBlock(int x, int y) {
	COORD curPos = GetCurrentCursorPos();
	SetCurrentCursorPos(x * 2, y);
	printf("☆");
	SetCurrentCursorPos(curPos.X, curPos.Y);
} // 지금은 안씀

void ShowNpcBlock()
{
	SetCurrentCursorPos(npcCurPosX, npcCurPosY);
	printf("★");
}

void DeleteBlock()
{

	SetCurrentCursorPos(npcCurPosX, npcCurPosY);
	printf("  ");
}

int NPC_moveLeft() {

	DeleteBlock();
	npcCurPosX -= 2;
	SetCurrentCursorPos(npcCurPosX, npcCurPosY);
	ShowNpcBlock();
	return 0;
	
}

int NPC_moveRight() {

	DeleteBlock();
	npcCurPosX += 2;
	SetCurrentCursorPos(npcCurPosX, npcCurPosY);
	ShowNpcBlock();

	return 0;

}

int NPC_moveUp() {
	
	DeleteBlock();
	npcCurPosY -= 1;
	SetCurrentCursorPos(npcCurPosX, npcCurPosY);
	ShowNpcBlock();

	return 0;
}

int NPC_moveDown() {

	DeleteBlock();
	npcCurPosY += 1;
	SetCurrentCursorPos(npcCurPosX, npcCurPosY);
	ShowNpcBlock();

	return 0;
}

int FindDstX() {
	srand((unsigned int)time(NULL));
	int x = rand() % 9;
	return x;
}// 지금은 안씀
int FindDstY() {
	srand((unsigned int)time(NULL));
	int y = rand() % 9;
	return y;
}// 지금은 안씀

int NpcMoving(clock_t current_game_time) {

	int npcX, npcY;

	npcX = npcCurPosX / 2;
	npcY = npcCurPosY;

	int dist = ShortestDistance(npcX, npcY); // 여기서 one_srt_dist 배열을 만들어줌 (이 배열을 보고 NPC가 움직임)

	int dx = npcX;
	int dy = npcY;

	SetCurrentCursorPos(npcCurPosX, npcCurPosY);


	NPC_current_Time = clock();

	while (1) { //이 while문 안에 있는 clock변수들은 신경쓰지 않아도 됨, 아직 테스트중, 아마 1칸씩 움직여야 하니까 while 지우는 방법도 고려
		if (one_srt_dist[dy][dx + 1] == 1) { // NPC 현재위치 기준 one_srt_dist의 오른쪽이 1이라면 (갈수있는길)
			one_srt_dist[dy][dx] = 0; // 현재 위치의 one_srt_dist를 0으로 초기화 하고

			if (NPC_current_Time - current_game_time > flagTime) {
				current_game_time = NPC_current_Time;
				NPC_moveRight(); //오른쪽으로 이동
			}
			dx += 1;
		}
		if (one_srt_dist[dy][dx - 1] == 1) {
			one_srt_dist[dy][dx] = 0;

			if (NPC_current_Time - current_game_time > flagTime) {
				current_game_time = NPC_current_Time;
				NPC_moveLeft();
			}
			dx -= 1;
		}
		if (one_srt_dist[dy + 1][dx] == 1) {
			one_srt_dist[dy][dx] = 0;

			if (NPC_current_Time - current_game_time > flagTime) {
				current_game_time = NPC_current_Time;
				NPC_moveDown();
			}
			dy += 1;
		}
		if (one_srt_dist[dy - 1][dx] == 1) {
			one_srt_dist[dy][dx] = 0;

			if (NPC_current_Time - current_game_time > flagTime) {
				current_game_time = NPC_current_Time;
				NPC_moveUp();
			}
			dy -= 1;
		}
		if (dx == dstX && dy == dstY) { // 목표 위치에 도착하면 mapModel의 상하좌우를 1로 초기화 하고 블럭을 지워줌 (임시 물풍선)
			mapModel[dstY + 1][dstX] = 0;
			mapModel[dstY - 1][dstX] = 0;
			mapModel[dstY][dstX + 1] = 0;
			mapModel[dstY][dstX - 1] = 0;
			SetCurrentCursorPos(dx * 2, dy);
			current_game_time = NPC_current_Time;
			block_break();
			break;
		}

		return 0;
	}
}
