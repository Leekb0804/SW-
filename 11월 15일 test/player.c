#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "player.h"
#include "map.h"
#include "cursor.h"
#include "bomb.h"

#include "define_state.h"

void ShowPlayerBlock()
{
    int x, y;

    COORD curPos = GetCurrentCursorPos();

    SetCurrentCursorPos(curPos.X, curPos.Y);
    printf("  ");
    SetCurrentCursorPos(curPos.X, curPos.Y);
    printf("��");
    SetCurrentCursorPos(curPos.X, curPos.Y);
}

void DeletePlayerBlock()
{
    int x, y;

    COORD curPos = GetCurrentCursorPos();

    if (checkObject_exist_bomb(curPos.X, curPos.Y) == 1)
    {
        SetCurrentCursorPos(curPos.X, curPos.Y);
        printf("��");
        SetCurrentCursorPos(curPos.X, curPos.Y);
    }
    else
    {
        SetCurrentCursorPos(curPos.X, curPos.Y);
        printf("  ");
        SetCurrentCursorPos(curPos.X, curPos.Y);
    }
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

    return checkObject_can_go(posX, posY);
}

void SetPlayerBomb() // ��ź���� �Լ�
{
    // ��ǥ (PlayerCurPosX, PlayerCurPosY)�� ��ź ���� �Լ�
    player_set_bomb();
}

int CheckPlayerState()
{
    // ���� �÷��̾� ��ǥ�� �������� ���� PlayerState ������Ʈ
    // ������Ʈ�� PlayerState ���� �°� ó��

    ////////////�߰�
    if (checkObject_bomb(PlayerCurPosX, PlayerCurPosY) == 1)
    {
        SetCurrentCursorPos(3, 16);
        printf("Player down    Game Over!\n");
        return (1);
    }
    return (0);
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
            case SPACE_BAR:
                SetPlayerBomb();
                //   ��ź�����Լ�;
                break;
            default:
                break;
            }
        }
        Sleep(25);
    }
}

void PlayerControl() // main �Լ��� �߰��ϼ���
{
    SetCurrentCursorPos(PlayerCurPosX, PlayerCurPosY);
    ShowPlayerBlock();

    ProcessKeyInput();
}
