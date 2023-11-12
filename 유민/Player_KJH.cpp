#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "Player_KJH.h"
#include "LeeGB_map.h"
#include "LeeGB_cursor.h"
#include "Test_Moving.h"

int PlayerCurPosX, PlayerCurPosY; // 플레이어 현재 좌표
int PlayerState = 1;           // 플레이어 현재 상태
clock_t Player_current_Time;
#define flagTime 0.7

void setPlayerCurPos() {
	PlayerCurPosX = 14; PlayerCurPosY = 1;
	SetCurrentCursorPos(PlayerCurPosX, PlayerCurPosY);
	ShowPlayerBlock();
}

void ShowPlayerBlock()
{


	SetCurrentCursorPos(PlayerCurPosX, PlayerCurPosY);
	printf("▣");
}

void DeletePlayerBlock()
{

	SetCurrentCursorPos(PlayerCurPosX, PlayerCurPosY);
	printf("  ");
}

void PlayerMoveLeft() // 플레이어 이동 (좌)
{
	if (!DetectCollision(PlayerCurPosX - 2, PlayerCurPosY))
	{
		return;
	}

	DeletePlayerBlock();

	PlayerCurPosX -= 2;

	SetCurrentCursorPos(PlayerCurPosX, PlayerCurPosY);
	ShowPlayerBlock();
}

void PlayerMoveRight() // 플레이어 이동 (우)
{
	if (!DetectCollision(PlayerCurPosX + 2, PlayerCurPosY))
	{
		return;
	}

	DeletePlayerBlock();

	PlayerCurPosX += 2;

	SetCurrentCursorPos(PlayerCurPosX, PlayerCurPosY);
	ShowPlayerBlock();
}

void PlayerMoveDown() // 플레이어 이동 (하)
{
	if (!DetectCollision(PlayerCurPosX, PlayerCurPosY + 1))
	{
		return;
	}

	DeletePlayerBlock();

	PlayerCurPosY += 1;

	SetCurrentCursorPos(PlayerCurPosX, PlayerCurPosY);
	ShowPlayerBlock();
}

void PlayerMoveUp() // 플레이어 이동 (상)
{
	if (!DetectCollision(PlayerCurPosX, PlayerCurPosY - 1))
	{
		return;
	}

	DeletePlayerBlock();

	PlayerCurPosY -= 1;

	SetCurrentCursorPos(PlayerCurPosX, PlayerCurPosY);
	ShowPlayerBlock();
}

int DetectCollision(int posX, int posY) // 임시로 장애물 GameBoardInfo로 설정하여 감지
{                              // 맵의 장애물에 맞춰 감지하도록 바꿀 예정
	int x, y;

	int arrX = posX / 2;
	int arrY = posY;
	
	return checkObject_can_go(arrX, arrY);
}

void SetPlayerBomb() // 폭탄놓는 함수
{
	// 좌표 (PlayerCurPosX, PlayerCurPosY)에 폭탄 놓는 함수
}

void CheckPlayerState()
{
	// 현재 플레이어 좌표의 정보값에 따라 PlayerState 업데이트
	// 업데이트된 PlayerState 값에 맞게 처리

	if (PlayerState == 0)
	{
		SetCurrentCursorPos(11, 0);
		puts("Game Over");
	}
}

void ProcessKeyInput(clock_t current_game_time)
{
	int key;
	for (int i = 0; i < 20; i++) {
		if (_kbhit() != 0)
		{
			key = _getch();
			Player_current_Time = clock();
			switch (key)
			{
			case LEFT:
				if (Player_current_Time - current_game_time > flagTime) {
					PlayerMoveLeft();
				}
				break;
			case RIGHT:
				if (Player_current_Time - current_game_time > flagTime) {
					PlayerMoveRight();
				}
				break;
			case UP:
				if (Player_current_Time - current_game_time > flagTime) {
					PlayerMoveUp();
				}
				break;
			case DOWN:
				if (Player_current_Time - current_game_time > flagTime) {
					PlayerMoveDown();
				}
				break;
				//case 폭탄놓는키:
				//   폭탄놓는함수; break;
			case SPACE:
				if (Player_current_Time - current_game_time > flagTime) {
					Player_break_block();
				}
				break;
			default:
				break;
			}
		}
		//Sleep(1);
	}
	
}

void Player_break_block() {


	SetCurrentCursorPos(PlayerCurPosX + 2, PlayerCurPosY);
	printf("  ");
	mapModel[PlayerCurPosY][(PlayerCurPosX + 2) / 2] = 0;
	SetCurrentCursorPos(PlayerCurPosX, PlayerCurPosY);

	SetCurrentCursorPos(PlayerCurPosX - 2, PlayerCurPosY);
	printf("  ");
	mapModel[PlayerCurPosY][(PlayerCurPosX - 2) / 2] = 0;
	SetCurrentCursorPos(PlayerCurPosX, PlayerCurPosY);

	SetCurrentCursorPos(PlayerCurPosX, PlayerCurPosY + 1);
	printf("  ");
	mapModel[PlayerCurPosY + 1][PlayerCurPosX / 2] = 0;
	SetCurrentCursorPos(PlayerCurPosX, PlayerCurPosY);

	SetCurrentCursorPos(PlayerCurPosX, PlayerCurPosY - 1);
	printf("  ");
	mapModel[PlayerCurPosY - 1][PlayerCurPosX / 2] = 0;
	SetCurrentCursorPos(PlayerCurPosX, PlayerCurPosY);
	
}

void PlayerControl(clock_t current_game_time) // main 함수에 추가하세요
{

	ProcessKeyInput(current_game_time);
	//NpcMoving();
}
