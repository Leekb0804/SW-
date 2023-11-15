#ifndef __MAP_H__
#define __MAP_H__

#include "bomb.h"
#include "define_state.h"

extern int mapModel[HEIGHT][WIDTH];

typedef struct map {
	int state;
	Bomb* bomb;
} Map;

int* output_random_5_num_arr();		//맵 랜덤 배치를 위한 랜덤 숫자 5개 생성 함수
void resetMap();		//맵 초기 값 설정
void generateMap();		//맵 생성
void drawMaps();		//맵 출력
//void draw_3_3maps(int x, int y, int cursX, int cursY);		//3*3 으로 확장

int checkObject_can_go(int cursorX, int cursorY);		//인자로 주어진 좌표로 이동할 수 있는지
int checkObject_bomb(int cursorX, int cursorY);			//인자로 주어진 좌표가 폭발범위인지
int checkObject_box(int cursorX, int cursorY);			//인자로 주어진 좌표에 부실 수 있는 장애물이 있는지
int checkObject_wall(int cursorX, int cursorY);			//인자로 주어진 좌표에 부실 수 없는 장애물이 있는지
int checkObject_exist_bomb(int cursorX, int cursorY);	//인자라 주어진 좌표에 터지지 않은 폭탄이 존재하는지

void gernerate_Item(int cursorX, int cursorY);          // 해당 좌표에 아이템 생성
void draw_Item_bomb_max(int x, int y);       // 해당 좌표에 bomb max 증가 아이템 출력
void draw_Item_bomb_range(int x, int y);     // 해당 좌표에 bomb max 증가 아이템 출력
void draw_Item_chracter_move(int x, int y); // 해당 좌표에 bomb max 증가 아이템 출력

int get_Player_starting_point_x();			//플레이어 초기 x 위치 지정
int get_Player_starting_point_y();			//플레이어 초기 y 위치 지정

void set_Bomb(int arrX, int arrY);				//해당좌표에 폭탄놓기		
void set_Empty(int arrX, int arrY);				//해당 좌표 공백으로 만들기
void set_Bomb_Boom(int arrX, int arrY);			//해당 좌표에 폭탄 폭발하게 만들기



#endif
