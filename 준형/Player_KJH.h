#ifndef __PLAYERKJH_H_
#define __PLAYERKJH_H_

#include <stdio.h>
#include <windows.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

int block_id;
int PlayerCurPosX, PlayerCurPosY; // �÷��̾� ���� ��ǥ
int PlayerState = 1;           // �÷��̾� ���� ����

typedef struct Player // �÷��̾� ����ü
{
    int Bomb_Count;
    int Span;
}Player;

void SetCurrentCursorPos(int x, int y);

COORD GetCurrentCursorPos(void);

void ShowPlayerBlock();
void DeletePlayerBlock();

void RemoveCursor(void);

void PlayerMoveLeft(); // �÷��̾� �̵� (��)
void PlayerMoveRight(); // �÷��̾� �̵� (��)
void PlayerMoveDown(); // �÷��̾� �̵� (��)
void PlayerMoveUp(); // �÷��̾� �̵� (��)
int DetectCollision(int posX, int posY); // �ӽ÷� ��ֹ� GameBoardInfo�� �����Ͽ� ����

void SetPlayerBomb(); // ��ź���� �Լ�
void CheckPlayerState();

void ProcessKeyInput();

void PlayerControl();

#endif