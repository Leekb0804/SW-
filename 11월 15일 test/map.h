#ifndef __MAP_H__
#define __MAP_H__

#include "bomb.h"
#include "define_state.h"

extern int mapModel[HEIGHT][WIDTH];

typedef struct map {
	int state;
	Bomb* bomb;
} Map;

int* output_random_5_num_arr();		//�� ���� ��ġ�� ���� ���� ���� 5�� ���� �Լ�
void resetMap();		//�� �ʱ� �� ����
void generateMap();		//�� ����
void drawMaps();		//�� ���
//void draw_3_3maps(int x, int y, int cursX, int cursY);		//3*3 ���� Ȯ��

int checkObject_can_go(int cursorX, int cursorY);		//���ڷ� �־��� ��ǥ�� �̵��� �� �ִ���
int checkObject_bomb(int cursorX, int cursorY);			//���ڷ� �־��� ��ǥ�� ���߹�������
int checkObject_box(int cursorX, int cursorY);			//���ڷ� �־��� ��ǥ�� �ν� �� �ִ� ��ֹ��� �ִ���
int checkObject_wall(int cursorX, int cursorY);			//���ڷ� �־��� ��ǥ�� �ν� �� ���� ��ֹ��� �ִ���
int checkObject_exist_bomb(int cursorX, int cursorY);	//���ڶ� �־��� ��ǥ�� ������ ���� ��ź�� �����ϴ���

void gernerate_Item(int cursorX, int cursorY);          // �ش� ��ǥ�� ������ ����
void draw_Item_bomb_max(int x, int y);       // �ش� ��ǥ�� bomb max ���� ������ ���
void draw_Item_bomb_range(int x, int y);     // �ش� ��ǥ�� bomb max ���� ������ ���
void draw_Item_chracter_move(int x, int y); // �ش� ��ǥ�� bomb max ���� ������ ���

int get_Player_starting_point_x();			//�÷��̾� �ʱ� x ��ġ ����
int get_Player_starting_point_y();			//�÷��̾� �ʱ� y ��ġ ����

void set_Bomb(int arrX, int arrY);				//�ش���ǥ�� ��ź����		
void set_Empty(int arrX, int arrY);				//�ش� ��ǥ �������� �����
void set_Bomb_Boom(int arrX, int arrY);			//�ش� ��ǥ�� ��ź �����ϰ� �����



#endif
