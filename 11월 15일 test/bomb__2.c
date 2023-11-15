#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "bomb.h"
#include "map.h"
#include "define_state.h"

//#include "debug.h"

extern int mapModel[HEIGHT][WIDTH];
extern int PlayerCurPosX; // 플레이어 현재 좌표 player.h 에서 선언
extern int PlayerCurPosY; // 플레이어 현재 좌표 player.h 에서 선언

extern int npcCurPosX;
extern int npcCurPosY;


int bomb_max = 3;
int bomb_len = 1;
int GameOver = 0;
unsigned long long cur_time;


BombHead* bombHead;
void TimeCheck();
Bomb* getBombNode(int x, int y);
void insertitem(Bomb* w);
void PrintBomb();
void ProcessKeyInput();
void ﻿BombSwich_On(int x, int y);
BombHead* init_List();



BombHead* init_List() {
    BombHead* list = (BombHead*)malloc(sizeof(BombHead));
    list->head = getBombNode(10, 10);
    return list;
}

Bomb* getBombNode(int x, int y) {
    Bomb* newbomb = (Bomb*)malloc(sizeof(Bomb));
    newbomb->prev = NULL;
    newbomb->next = NULL;
    newbomb->start_time = clock(); // 현재 시간으로 초기화
    //newbomb->time = 0;
    newbomb->x = x;
    newbomb->y = y;
    return newbomb;
}

void insertitem(Bomb* w) {
    Bomb* curBomb = bombHead->head;

    if (bombHead->head == NULL)
    {
        bombHead->head = w;
    }
    else
    {
        while (curBomb->next != NULL) {
            //if (curBomb->x == w->x && curBomb->y == w->y) return //이미 물풍선이 있는 곳에 또 물풍선을 놓으려고 하면 리턴
            curBomb = curBomb->next;
        }
        curBomb->next = w;
        w->prev = curBomb;
    }
    set_Bomb(w->x, w->y); //물풍선 놓기.
}

void PrintBomb() { //폭탄 배열 위치 출력하기
    Bomb* curBomb = bombHead->head;
    while (curBomb->next != NULL) {
        curBomb = curBomb->next;
        printf("%d %d\n", curBomb->x, curBomb->y);
    }
}

//void ProcessKeyInput() {
//    int i = 0, key = 0;
//    for (i = 0; i < 30; i++) {
//        if (_kbhit() != 0) {
//            key = _getch();
//            switch (key) {
//            case 'q': { //물풍선 설치키
//                //x, y키에 대해선 수정이 필요함. to 준형이에게
//                int x = rand() % 8; //플레이어의 위치를 일단 임의로 받아옴. 
//                int y = rand() % 8; //실제 코드에서는 GetCurrentCursorPos를 사용하여 x,y값을 지정할 것.
//                Bomb* newbomb = getBombNode(x, y); //x, y좌표의 새 폭탄 얻어옴.
//                insertitem(newbomb);
//                //PrintBomb();
//            }
//                    break;
//            case 'p': //현재 물풍선들의 좌표 출력
//                PrintBomb();
//                break;
//            }
//        }
//        Sleep(10);
//    }
//    //TimeCheck();
//}

void ﻿BombSwich_On(int x, int y) {
    Bomb* curBomb = bombHead->head;

    while (curBomb != NULL) {
        if (curBomb->x == x && curBomb->y == y) {
            //PBpmb = curBomb;
            break;
        }
        curBomb = curBomb->next;
    }

    if (curBomb == NULL)
        return;

    //mapModel[curBomb->y][curBomb->x] == 0; //맵 정보 수정. 물풍선 있던 자리에 아무것도 출력하지 않음.

    set_Bomb_Boom(curBomb->x, curBomb->y);

    if (curBomb->prev == NULL)
        bombHead->head = curBomb->next;
    else
        curBomb->prev->next = curBomb->next;
    if (curBomb->next != NULL)
        curBomb->next->prev = curBomb->prev;

    free(curBomb);
    //printf("%d %d BOMB!!!\n", x, y);

    for (int i = -bomb_len; i <= bomb_len; i++) { //폭탄이 터지는 범위 훑기


        if (i == 0) continue;
        int m = i + y;
        int n = i + x;
        

        //세로줄 확인

        if (m < 0 || HEIGHT <= m)
            ; //맵밖으로 벗어나면 continue  -> 가로줄 실행 안함        //이경빈이 만들 것 /////////////////////////////
        else if (checkObject_can_go(x * 2 + GBOARD_ORIGIN_X, m + GBOARD_ORIGIN_Y) == 1)
            set_Bomb_Boom(x, m);
        else if (checkObject_box(x * 2 + GBOARD_ORIGIN_X, m + GBOARD_ORIGIN_Y) == 1) { //나무 상자라면
            //mapModel[m][x] == 0; //나무 상자 파괴
            set_Empty(x, m);
            gernerate_Item(x * 2 + GBOARD_ORIGIN_X, m + GBOARD_ORIGIN_Y);

            //여기에 아이템 랜덤 드랍 함수. to 경빈이에게
        }
        else if (mapModel[m][x] == 111 || mapModel[m][x] == 222 || mapModel[m][x] == 333) { //아이템이 있다면
            mapModel[m][x] = 0; //아이템 파괴
        }
        else if (mapModel[m][x] == 400) { //만약 다른 폭탄이 있다면
            ﻿BombSwich_On(x, m); //재귀호출
        }
        else
            ;


        //가로줄 확인
        if (n < 0 || WIDTH <= n)
            ; //맵밖으로 벗어나면 continue
        else if (checkObject_can_go(n * 2 + GBOARD_ORIGIN_X, y + GBOARD_ORIGIN_Y) == 1)
            set_Bomb_Boom(n, y);
        else if (mapModel[y][n] == 1) { //나무 상자라면
            mapModel[y][n] = 0; //나무 상자 파괴
            //여기에 아이템 랜덤 드랍 함수. to 경빈이에게
            set_Empty(n, y);
            gernerate_Item(n * 2 + GBOARD_ORIGIN_X, y + GBOARD_ORIGIN_Y);
        }
        else if (mapModel[y][n] == 111 || mapModel[y][n] == 222 || mapModel[y][n] == 333) { //아이템이 있다면
            mapModel[y][n] = 0; //아이템 파괴
        }
        else if (mapModel[y][n] == 400) { //만약 다른 폭탄이 있다면
            ﻿BombSwich_On(n, y); //재귀호출
        }

    }

}

void TimeCheck() {
    Bomb* curBomb = bombHead->head;
    if (curBomb == NULL)
        return;
    //if (curBomb->next == NULL) return;
    
    Bomb* tmpBomb = curBomb->next;

    while (curBomb != NULL) {
        cur_time = clock();
        tmpBomb = curBomb->next;
        if (cur_time - curBomb->start_time >= 3000) { //3초가 지났으면 물풍선 폭파
            ﻿BombSwich_On(curBomb->x, curBomb->y);
            //여기에 맵 다시 그려야함. to 경빈이에게
        }
        curBomb = tmpBomb;
    }
}


void player_set_bomb()
{
    Bomb* newbomb = getBombNode((PlayerCurPosX - GBOARD_ORIGIN_X) / 2, (PlayerCurPosY - GBOARD_ORIGIN_Y)); //x, y좌표의 새 폭탄 얻어옴.
    insertitem(newbomb);
}

void npc_set_bomb()
{
    Bomb* newbomb = getBombNode((npcCurPosX - GBOARD_ORIGIN_X) / 2, (npcCurPosY - GBOARD_ORIGIN_Y)); //x, y좌표의 새 폭탄 얻어옴.
    insertitem(newbomb);
}





//int main() {
//    srand((unsigned)time(NULL));
//    unsigned long long start_time = clock(); // 프로그램 시작 시간 저장
//    unsigned long long delay = 3 * CLOCKS_PER_SEC; // 3초를 클럭 틱으로 변환
//
//    bombHead = init_List();
//
//
//    char x;
//
//    while (1) {
//        ProcessKeyInput();
//        TimeCheck();
//    }
//    /*  while (clock() < start_time + delay) {
//          // 기다리는 동안 아무 작업도 하지 않음
//      }*/
//
//    return 0;
//}