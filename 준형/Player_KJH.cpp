#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "Player_KJH.h"
#include "LeeGB_map.h"

void SetCurrentCursorPos(int x, int y)
{
    COORD pos = { x, y };

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

COORD GetCurrentCursorPos(void)
{
    COORD curPoint;

    CONSOLE_SCREEN_BUFFER_INFO curInfo;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curPoint.X = curInfo.dwCursorPosition.X;
    curPoint.Y = curInfo.dwCursorPosition.Y;

    return curPoint;
}

void ShowPlayerBlock()
{
    int x, y;

    COORD curPos = GetCurrentCursorPos();

    SetCurrentCursorPos(curPos.X, curPos.Y);
    printf("��");
    SetCurrentCursorPos(curPos.X, curPos.Y);
}

void DeletePlayerBlock()
{
    int x, y;

    COORD curPos = GetCurrentCursorPos();

    SetCurrentCursorPos(curPos.X, curPos.Y);
    printf("  ");
    SetCurrentCursorPos(curPos.X, curPos.Y);
}

void RemoveCursor(void)
{
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void PlayerMoveLeft() // �÷��̾� �̵� (��)
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

void PlayerMoveRight() // �÷��̾� �̵� (��)
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

void PlayerMoveDown() // �÷��̾� �̵� (��)
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

void PlayerMoveUp() // �÷��̾� �̵� (��)
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

int DetectCollision(int posX, int posY) // �ӽ÷� ��ֹ� GameBoardInfo�� �����Ͽ� ����
{                              // ���� ��ֹ��� ���� �����ϵ��� �ٲ� ����
    int x, y;

    int arrX = posX / 2;
    int arrY = posY;

    /*
    if (gameBoardInfo[arrY][arrX] == 1)
        return 0;    
    */
    return checkObject_can_go(arrX, arrY);

    return 1;
}

void SetPlayerBomb() // ��ź���� �Լ�
{
    // ��ǥ (PlayerCurPosX, PlayerCurPosY)�� ��ź ���� �Լ�
}

void CheckPlayerState()
{
    // ���� �÷��̾� ��ǥ�� �������� ���� PlayerState ������Ʈ
    // ������Ʈ�� PlayerState ���� �°� ó��

    if (PlayerState == 0)
    {
        SetCurrentCursorPos(11, 0);
        puts("Game Over");
    }
}

void ProcessKeyInput()
{
    int key;

    for (int i = 0; i < 20; i++)
    {
        if (_kbhit() != 0)
        {
            key = _getch();
            switch (key)
            {
            case LEFT:
                PlayerMoveLeft(); break;
            case RIGHT:
                PlayerMoveRight(); break;
            case UP:
                PlayerMoveUp(); break;
            case DOWN:
                PlayerMoveDown(); break;
                //case ��ź����Ű:
                //   ��ź�����Լ�; break;
            default:
                break;
            }
        }
        Sleep(25);
    }
}

void PlayerControl() // main �Լ��� �߰��ϼ���
{
    RemoveCursor();

    PlayerCurPosX = 10; PlayerCurPosY = 2;
    SetCurrentCursorPos(PlayerCurPosX, PlayerCurPosY);
    ShowPlayerBlock();

    while (1)
    {
        CheckPlayerState();
        ProcessKeyInput();
    }
}