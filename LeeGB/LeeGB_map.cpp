#include "LeeGB_map.h"

#include <stdio.h>	//����׿�
#include <stdlib.h> //rand(), srand() �Լ�
#include <time.h>	//time(NULL) ����ϱ� ����

#include "LeeGB_cursor.h"

char mapModel[9][9] =
	{
		{1, 0, 1, 0, 0, 0, 1, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 1, 0, 0, 0, 1, 0, 1},

		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},

		{1, 0, 1, 0, 0, 0, 1, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 1, 0, 0, 0, 1, 0, 1}};

int *output_random_5_num_arr()
{
	int test[10] = {
		0,
	};
	int *num = (int *)malloc(sizeof(int) * 5);
	int random_num;
	int i = 0;

	// �ߺ��� ���� Ȯ���ϱ� ���� test[10]�迭�� ����
	// random_num �� �ϳ� ������ test�迭�� Ȯ��
	// test[random_num]�� ���� 1�� �ƴϸ�
	// test[random_num]�� ���� 1���� �� num�迭�� random_num �� �߰�
	// num �迭�� �� ä�ﶧ ���� �� ���� �ݺ�

	while (i < 5)
	{
		random_num = (rand() % 9); // 0 ~ 8 �߿� ������ ��
		if (test[random_num] == 0)
		{
			test[random_num] = 1;
			num[i] = random_num;
			++i;
		}
	}

	// ����׿�
	/*for (i = 0; i < 5; ++i)
		printf(" %d", num[i]);
	printf("\n");*/

	return num;
}

void resetMap() // ���� ��, ���� �Ʒ�, ������ ��, ������ �Ʒ� ó�� �����Ҷ�, ���ڰ��� ������ �� �ֵ��� �ʱ�ȭ
{
	mapModel[1 - 1][1 - 1] = 1;
	mapModel[1 - 1][1 + 1] = 1;
	mapModel[1 + 1][1 - 1] = 1;
	mapModel[1 + 1][1 + 1] = 1;

	mapModel[7 - 1][1 - 1] = 1;
	mapModel[7 - 1][1 + 1] = 1;
	mapModel[7 + 1][1 - 1] = 1;
	mapModel[7 + 1][1 + 1] = 1;

	mapModel[1 - 1][7 - 1] = 1;
	mapModel[1 - 1][7 + 1] = 1;
	mapModel[1 + 1][7 - 1] = 1;
	mapModel[1 + 1][7 + 1] = 1;

	mapModel[7 - 1][7 - 1] = 1;
	mapModel[7 - 1][7 + 1] = 1;
	mapModel[7 + 1][7 - 1] = 1;
	mapModel[7 + 1][7 + 1] = 1;
}

void generateMap() // �ʻ���
{
	resetMap();

	srand(time(NULL));
	int *num = output_random_5_num_arr();
	/*
	0 = 0			/ 1 = 1				/ 2 = 2
	3 = 1 * 3 + 0	/ 4 = 1 * 3 + 1		/ 5 = 1 * 3 + 2
	6 = 2 * 3 + 0	/ 7 = 2 * 3 + 1		/ 8 = 2 * 3 + 2
	*/

	/*
	map�� ������
	1 2 3
	4 5 6
	7 8 9 �� ����������
	*/
	// 4������ ä���
	for (int i = 0; i < 5; ++i)
	{
		mapModel[(num[i] / 3)][3 + num[i] % 3] = 1;
	}

	// 2������ ä���
	num = output_random_5_num_arr();
	for (int i = 0; i < 5; ++i)
	{
		mapModel[3 + (num[i] / 3)][num[i] % 3] = 1;
	}
	free(num);

	// 5������ ä���
	num = output_random_5_num_arr();
	for (int i = 0; i < 5; ++i)
	{
		mapModel[3 + (num[i] / 3)][3 + num[i] % 3] = 1;
	}
	free(num);

	// 8������ ä���
	num = output_random_5_num_arr();
	for (int i = 0; i < 5; ++i)
	{
		mapModel[3 + (num[i] / 3)][6 + num[i] % 3] = 1;
	}
	free(num);

	// 6������ ä���
	num = output_random_5_num_arr();
	for (int i = 0; i < 5; ++i)
	{
		mapModel[6 + (num[i] / 3)][3 + num[i] % 3] = 1;
	}
	free(num);

	// debug
	/*for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j)
			printf(" %d", mapModel[i][j]);
		printf("\n");
	}*/
}

void drawMaps() // ���� ȭ�鿡 ���
{
	int x, y;
	int cursX, cursY;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			cursX = x * 2 + GBOARD_ORIGIN_X; /*GBOARD_ORIGIN_X*/
			;
			cursY = y + GBOARD_ORIGIN_Y; /*GBOARD_ORIGIN_Y*/
			;

			SetCurrentCursorPos(cursX, cursY);

			if (mapModel[y][x] == 1)
			{
				printf("��");
			}
			else
			{
				printf("");
			}

			// draw_3_3maps(x, y, cursX, cursY);		//�迭�� 1ĭ�� ȭ���� 3*3 ũ��� ǥ��
		}
	}
	SetCurrentCursorPos((GBOARD_ORIGIN_X /*BOARD_ORIGIN_X*/ + WIDTH * 2 + 1), HEIGHT + 1);
}

void draw_3_3maps(int x, int y, int cursX, int cursY)
{
	for (int yy = 0; yy < 3; ++yy)
	{
		for (int xx = 0; xx < 3; ++xx)
		{
			SetCurrentCursorPos(cursX + xx * 2, cursY + yy); // �׸� ��ĭ�� Ŀ�� 2���� �����ϹǷ� 2 * xx�� �ϸ� Ŀ����ġ ����

			if (mapModel[y][x] == 1)
			{
				printf("��");
			}
			else
			{
				printf("  ");
			}
		}
	}
}
