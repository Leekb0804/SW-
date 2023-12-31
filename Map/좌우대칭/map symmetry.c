#define WIDTH 17
#define HEIGHT 17

#define GBOARD_ORIGIN_X 0
#define GBOARD_ORIGIN_Y 0

#define STATE_EMPTY 0
#define STATE_ITEM_BOMB_MAX 111
#define STATE_ITEM_BOMB_RANGE 222
#define STATE_ITEM_CHARACTER_MOVE 333
#define STATE_BOMB_SETTING 400
#define STATE_BOMB_BOOM 444
#define STATE_BOX 1
#define STATE_WALL 999


#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>


int mapModel[HEIGHT][WIDTH] =
{
	{STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL},

	{STATE_WALL,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_BOX,STATE_BOX,STATE_BOX,STATE_BOX,STATE_BOX,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_WALL},
	{STATE_WALL,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_BOX,STATE_BOX,STATE_BOX,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_WALL},
	{STATE_WALL,STATE_EMPTY,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_BOX,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_EMPTY,STATE_WALL},

	{STATE_WALL,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_WALL},
	{STATE_WALL,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_WALL},
	{STATE_WALL,STATE_BOX,STATE_BOX,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_BOX,STATE_BOX,STATE_WALL},

	{STATE_WALL,STATE_BOX,STATE_BOX,STATE_BOX,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_BOX,STATE_BOX,STATE_BOX,STATE_WALL},
	{STATE_WALL,STATE_BOX,STATE_BOX,STATE_BOX,STATE_BOX,STATE_BOX,STATE_EMPTY,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_EMPTY,STATE_BOX,STATE_BOX,STATE_BOX,STATE_BOX,STATE_BOX,STATE_WALL},
	{STATE_WALL,STATE_BOX,STATE_BOX,STATE_BOX,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_BOX,STATE_BOX,STATE_BOX,STATE_WALL},

	{STATE_WALL,STATE_BOX,STATE_BOX,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_BOX,STATE_BOX,STATE_WALL},
	{STATE_WALL,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_WALL},
	{STATE_WALL,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_WALL},

	{STATE_WALL,STATE_EMPTY,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_BOX,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_BOX,STATE_EMPTY,STATE_EMPTY,STATE_WALL},
	{STATE_WALL,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_BOX,STATE_BOX,STATE_BOX,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_WALL},
	{STATE_WALL,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_BOX,STATE_BOX,STATE_BOX,STATE_BOX,STATE_BOX,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_EMPTY,STATE_WALL},

	{STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL,STATE_WALL}
};

void SetCurrentCursorPos(int x, int y)
{
	COORD pos = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void drawMaps()		//맵을 화면에 출력
{
	int x, y;
	int cursX, cursY;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH; x++)
		{
			cursX = x * 2 + GBOARD_ORIGIN_X; /*GBOARD_ORIGIN_X*/;
			cursY = y + GBOARD_ORIGIN_Y; /*GBOARD_ORIGIN_Y*/;

			SetCurrentCursorPos(cursX, cursY);

			if (mapModel[y][x] == STATE_BOX)
			{
				printf("■");
			}
			else if (mapModel[y][x] == STATE_WALL)
			{
				printf("▩");
			}
			else { printf("  "); }

			//draw_3_3maps(x, y, cursX, cursY);		//배열의 1칸을 화면의 3*3 크기로 표현
		}
	}
	SetCurrentCursorPos((GBOARD_ORIGIN_X/*BOARD_ORIGIN_X*/ + WIDTH * 2 + 1), HEIGHT + 1);
}

int main() {
	drawMaps();
	getchar();
}