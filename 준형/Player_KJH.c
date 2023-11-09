#include <stdio.h>
#include <windows.h>

#define GBOARD_WIDTH 10
#define GBOARD_HEIGHT 20
#define GBOARD_ORIGIN_X 4
#define GBOARD_ORIGIN_Y 2

int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2] = { 0 };

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

int block_id;
int speed;
int PlayerCurPosX, PlayerCurPosY; // �÷��̾� ���� ��ǥ
int PlayerState = 1;           // �÷��̾� ���� ����

typedef struct Player // �÷��̾� ����ü
{
    int Bomb_Count;
    int Span;
}Player;

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

    int arrX = (posX - GBOARD_ORIGIN_X) / 2;
    int arrY = posY - GBOARD_ORIGIN_Y;

    if (gameBoardInfo[arrY][arrX] == 1) // �ӽ÷� gameBoardInfo�� ��ֹ� �Ǵ��ϰ� �س���
        return 0;

    return 1;
}

COORD SetPlayerBomb() // ��ź���� �Լ�
{
    // ��ǥ (PlayerCurPosX, PlayerCurPosY)�� ��ź ���� �Լ�
}

void CheckPlayerState()
{
    // ���� �÷��̾� ��ǥ�� �������� ���� PlayerState ������Ʈ
    // ������Ʈ�� PlayerState ���� �°� ó��

    if (PlayerState = 0)
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

void DrawGameBoard()
{
    int x, y;
    for (y = 0; y <= GBOARD_HEIGHT; y++)
    {
        SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);
        if (y == GBOARD_HEIGHT)
            printf("��");
        else
            printf("��");
    }
    for (y = 0; y <= GBOARD_HEIGHT; y++)
    {
        SetCurrentCursorPos(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y);
        if (y == GBOARD_HEIGHT)
            printf("��");
        else
            printf("��");
    }
    for (x = 1; x < GBOARD_WIDTH + 1; x++)
    {
        SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT);
        printf("��");
    }

    PlayerCurPosX = GBOARD_ORIGIN_X + GBOARD_WIDTH;
    PlayerCurPosY = 0;
    SetCurrentCursorPos(PlayerCurPosX, PlayerCurPosY);
}

int main()
{
    RemoveCursor();
    speed = 25;

    DrawGameBoard(); // �ӽ� ��ֹ�

    for (int y = 0; y < GBOARD_HEIGHT; y++)
    {
        gameBoardInfo[y][0] = 1;
        gameBoardInfo[y][GBOARD_WIDTH + 1] = 1;
    }
    for (int x = 0; x < GBOARD_WIDTH + 2; x++)
    {
        gameBoardInfo[GBOARD_HEIGHT][x] = 1;
    }

    PlayerCurPosX = 10; PlayerCurPosY = 2;
    SetCurrentCursorPos(PlayerCurPosX, PlayerCurPosY);
    ShowPlayerBlock();

    while (1)
    {
        CheckPlayerState();
        ProcessKeyInput();
    }

    return 0;
}