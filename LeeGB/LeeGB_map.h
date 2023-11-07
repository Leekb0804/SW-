#ifndef __MAP_H__
#define __MAP_H__

#include "../define_state.h"

extern char mapModel[HEIGHT][WIDTH];

int *output_random_5_num_arr();
void resetMap();
void generateMap();
void drawMaps();
void draw_3_3maps(int x, int y, int cursX, int cursY);

int checkObject_can_go(int x, int y); // ���ڷ� �־��� ��ǥ�� �̵��� �� �ִ���
int checkObject_bomb(int x, int y);   // ���ڷ� �־��� ��ǥ�� ���߹�������
int checkObject_box(int x, int y);    // ���ڷ� �־��� ��ǥ�� �ν� �� �ִ� ��ֹ��� �ִ���
int checkObject_wall(int x, int y);   // ���ڷ� �־��� ��ǥ�� �ν� �� ���� ��ֹ��� �ִ���

#endif
