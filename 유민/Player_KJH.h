#pragma once

#ifndef __PLAYERKJH_H_
#define __PLAYERKJH_H_

#include <stdio.h>
#include <windows.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32

extern int PlayerCurPosX, PlayerCurPosY;
extern int PlayerState;
extern clock_t Player_current_Time;

typedef struct Player // 플레이어 구조체
{
	int Bomb_Count;
	int Span;
}Player;

void setPlayerCurPos();
void ShowPlayerBlock();
void DeletePlayerBlock();

void PlayerMoveLeft(); // 플레이어 이동 (좌)
void PlayerMoveRight(); // 플레이어 이동 (우)
void PlayerMoveDown(); // 플레이어 이동 (하)
void PlayerMoveUp(); // 플레이어 이동 (상)
int DetectCollision(int posX, int posY); // 임시로 장애물 GameBoardInfo로 설정하여 감지

void SetPlayerBomb(); // 폭탄놓는 함수
void CheckPlayerState();

void ProcessKeyInput(clock_t current_game_time);
void Player_break_block();

void PlayerControl(clock_t current_game_time);

#endif
