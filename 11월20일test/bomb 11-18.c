#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "bomb 11-18.h"
#include "map.h"
#include "define_state.h"

#include "player.h"

//#include "debug.h"

extern int mapModel[HEIGHT][WIDTH];
extern int PlayerCurPosX; // 플레이어 현재 좌표 player.h 에서 선언
extern int PlayerCurPosY; // 플레이어 현재 좌표 player.h 에서 선언

extern int npcCurPosX;
extern int npcCurPosY;

unsigned long long cur_time;
int GameOver = 0;

BombHead* bombHead;
BOOMHead* boomhead;

extern int player_bomb_len;

Bomb* getBombNode(int x, int y)
{
    Bomb* newbomb = (Bomb*)malloc(sizeof(Bomb));
    newbomb->prev = NULL;
    newbomb->next = NULL;
    newbomb->start_time = clock(); // 현재 시간으로 초기화
    //newbomb->time = 0;
    newbomb->x = x;
    newbomb->y = y;
    newbomb->len = player_bomb_len;
    return newbomb;
}

void insertitem(Bomb* w)
{
    Bomb* curBomb = bombHead->next;

    if (bombHead->next == NULL)
    {
        bombHead->next = w;
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
    bomb_exist_count++;
}

BOOM* getnode_BOOM(int x, int y, unsigned long long time)
{
    BOOM* newBOOM = (BOOM*)malloc(sizeof(BOOM));
    newBOOM->start_time = time;
    newBOOM->x = x;
    newBOOM->y = y;
    newBOOM->prev = NULL;
    newBOOM->next = NULL;
    return newBOOM;
}

void insertitem_BOOM(BOOM* w)
{
    if (boomhead->next == NULL) {
        boomhead->next = w;
        return;
    }

    BOOM* curBOOM = boomhead->next;
    while (curBOOM->next != NULL) {
        curBOOM = curBOOM->next;
    }
    curBOOM->next = w;
    w->prev = curBOOM;
}

void PrintBomb()
{ //폭탄 배열 위치 출력하기
    Bomb* curBomb = bombHead->next;
    while (curBomb->next != NULL) {
        printf("%d %d\n", curBomb->x, curBomb->y);
        curBomb = curBomb->next;
    }
}

void printBOOM()
{
    BOOM* curBOOM = boomhead->next;
    if (curBOOM == NULL) return;

    while (curBOOM != NULL) {
        printf("%d %d\n", curBOOM->x, curBOOM->y);
        curBOOM = curBOOM->next;
    }
}

void ?BombSwich_On(int x, int y)
{
    unsigned long long time = clock();
    bomb_exist_count--;
    Bomb* curBomb = bombHead->next;

    // x, y 를 가지는 노드를 찾는 함수 만들기
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
    BOOM* w = getnode_BOOM(curBomb->x, curBomb->y, time);
    insertitem_BOOM(w);

    // 노드 삭제 함수 만들기
    if (curBomb->prev == NULL)
        bombHead->next = curBomb->next;
    else
        curBomb->prev->next = curBomb->next;
    if (curBomb->next != NULL)
        curBomb->next->prev = curBomb->prev;
    int len = curBomb->len;
    free(curBomb);
    //printf("%d %d BOMB!!!\n", x, y);

    //printf("len : %d", len);
    


    //위로 터지는 범위 훑기
    for (int i = 1; i <= len; i++)
    {
        if (check_over_GameBoard_HEIGHT(y - i))
            break;
        else if (checkObject_can_go(arrX_to_cursorX(x), arrY_to_cursorY(y - i))) {
            set_Bomb_Boom(x, y - i);
            w = getnode_BOOM(x, y - i, time);
            insertitem_BOOM(w);
        }
        else if (checkObject_box(arrX_to_cursorX(x), arrY_to_cursorY(y - i))) { //나무 상자라면
            set_Empty(x, y - i);
            gernerate_Item(arrX_to_cursorX(x), arrY_to_cursorY(y - i));
            break;          // 나무 상자 뒤로 폭탄의 범위가 퍼지지 않게
        }
        else if (checkObject_Item(arrX_to_cursorX(x), arrY_to_cursorY(y - i))) { //아이템이 있다면
            set_Empty(x, y - i);     //아이템 파괴, 공백으로 변경
        }
        else if (checkObject_exist_bomb(arrX_to_cursorX(x), arrY_to_cursorY(y - i))) { //만약 다른 폭탄이 있다면
            ?BombSwich_On(x, y - i); //재귀호출
        }
        else
            ;
    }
    //아래로 터지는 범위 훑기
    for (int i = 1; i <= len; i++)
    {
        if (check_over_GameBoard_HEIGHT(y + i))
            break;
        else if (checkObject_can_go(arrX_to_cursorX(x), arrY_to_cursorY(y + i))) {
            set_Bomb_Boom(x, y + i);
            w = getnode_BOOM(x, y + i, time);
            insertitem_BOOM(w);
        }
        else if (checkObject_box(arrX_to_cursorX(x), arrY_to_cursorY(y + i))) { //나무 상자라면
            set_Empty(x, y + i);
            gernerate_Item(arrX_to_cursorX(x), arrY_to_cursorY(y + i));
            break;          // 나무 상자 뒤로 폭탄의 범위가 퍼지지 않게
        }
        else if (checkObject_Item(arrX_to_cursorX(x), arrY_to_cursorY(y + i))) { //아이템이 있다면
            set_Empty(x, y + i);     //아이템 파괴, 공백으로 변경
        }
        else if (checkObject_exist_bomb(arrX_to_cursorX(x), arrY_to_cursorY(y + i))) { //만약 다른 폭탄이 있다면
            ?BombSwich_On(x, y + i); //재귀호출
        }
        else
            ;
    }
    // 좌로 터지는 범위 훑기
    for (int i = 1; i <= len; i++)
    {
        if (check_over_GameBoard_Width(x - i))
            break;
        else if (checkObject_can_go(arrX_to_cursorX(x- i), arrY_to_cursorY(y))) {
            set_Bomb_Boom(x - i, y);
            w = getnode_BOOM(x - i, y, time);
            insertitem_BOOM(w);
        }
        else if (checkObject_box(arrX_to_cursorX(x - i), arrY_to_cursorY(y))) { //나무 상자라면
            set_Empty(x - i, y);
            gernerate_Item(arrX_to_cursorX(x - i), arrY_to_cursorY(y));
            break;          // 나무 상자 뒤로 폭탄의 범위가 퍼지지 않게
        }
        else if (checkObject_Item(arrX_to_cursorX(x - i), arrY_to_cursorY(y))) { //아이템이 있다면
            set_Empty(x - i, y);     //아이템 파괴, 공백으로 변경
        }
        else if (checkObject_exist_bomb(arrX_to_cursorX(x - i), arrY_to_cursorY(y))) { //만약 다른 폭탄이 있다면
            ?BombSwich_On(x - i, y); //재귀호출
        }
        else
            ;
    }
    // 우로 터지는 범위 훑기
    for (int i = 1; i <= len; i++)
    {
        if (check_over_GameBoard_Width(x + i))
            break;
        else if (checkObject_can_go(arrX_to_cursorX(x + i), arrY_to_cursorY(y))) {
            set_Bomb_Boom(x + i, y);
            w = getnode_BOOM(x + i, y, time);
            insertitem_BOOM(w);
        }
        else if (checkObject_box(arrX_to_cursorX(x + i), arrY_to_cursorY(y))) { //나무 상자라면
            set_Empty(x + i, y);
            gernerate_Item(arrX_to_cursorX(x + i), arrY_to_cursorY(y));
            break;          // 나무 상자 뒤로 폭탄의 범위가 퍼지지 않게
        }
        else if (checkObject_Item(arrX_to_cursorX(x + i), arrY_to_cursorY(y))) { //아이템이 있다면
            set_Empty(x + i, y);     //아이템 파괴, 공백으로 변경
        }
        else if (checkObject_exist_bomb(arrX_to_cursorX(x + i), arrY_to_cursorY(y))) { //만약 다른 폭탄이 있다면
            ?BombSwich_On(x + i, y); //재귀호출
        }
        else
            ;
    }

    //for (int i = -len; i <= len; i++) { //폭탄이 터지는 범위 훑기
    //    if (i == 0) continue;
    //    int m = i + y;
    //    int n = i + x;

    //    //세로줄 확인
    //    if (check_over_GameBoard_HEIGHT(m))
    //        ;
    //    else if (checkObject_can_go(arrX_to_cursorX(x), arrY_to_cursorY(m))) {
    //        set_Bomb_Boom(x, m);
    //        w = getnode_BOOM(x, m, time);
    //        insertitem_BOOM(w);
    //    }
    //    else if (checkObject_box(arrX_to_cursorX(x), arrY_to_cursorY(m))) { //나무 상자라면
    //        set_Empty(x, m);
    //        gernerate_Item(arrX_to_cursorX(x), arrY_to_cursorY(m));
    //    }
    //    else if (checkObject_Item(arrX_to_cursorX(x), arrY_to_cursorY(m))) { //아이템이 있다면
    //        set_Empty(x, m);     //아이템 파괴, 공백으로 변경
    //    }
    //    else if (checkObject_exist_bomb(arrX_to_cursorX(x), arrY_to_cursorY(m))) { //만약 다른 폭탄이 있다면
    //        ?BombSwich_On(x, m); //재귀호출
    //    }
    //    else
    //        ;

    //    //가로줄 확인
    //    if (check_over_GameBoard_Width(n))          //맵밖으로 벗어난 경우
    //        ;
    //    else if (checkObject_can_go(arrX_to_cursorX(n), arrY_to_cursorY(y))) {
    //        set_Bomb_Boom(n, y);
    //        w = getnode_BOOM(n, y, time);
    //        insertitem_BOOM(w);
    //    }
    //    else if (checkObject_box(arrX_to_cursorX(n), arrY_to_cursorY(y))) { //나무 상자라면
    //        set_Empty(n, y);
    //        gernerate_Item(arrX_to_cursorX(n), arrY_to_cursorY(y));
    //    }
    //    else if (checkObject_Item(arrX_to_cursorX(n), arrY_to_cursorY(y))) { //아이템이 있다면
    //        set_Empty(n, y); //아이템 파괴
    //    }
    //    else if (checkObject_exist_bomb(arrX_to_cursorX(n), arrY_to_cursorY(y))) { //만약 다른 폭탄이 있다면
    //        ?BombSwich_On(n, y); //재귀호출
    //    }

    //}
    
    //printBOOM();
}

void TimeCheck()
{
    Bomb* curBomb = bombHead->next;
    if (curBomb == NULL)
        return;

    Bomb* tmpBomb;

    while (curBomb != NULL) {
        cur_time = clock();
        tmpBomb = curBomb->next;
        if (cur_time - curBomb->start_time >= 3000) {
            ?BombSwich_On(curBomb->x, curBomb->y);
            break;
        }
        curBomb = tmpBomb;
    }
}

void TimeCheck_BOOM()
{
    BOOM* curBOOM = boomhead->next;
    if (curBOOM == NULL) return;
    BOOM* tmpBOOM = curBOOM->next;
    while (curBOOM != NULL) {
        cur_time = clock();
        tmpBOOM = curBOOM->next;
        if (cur_time - curBOOM->start_time >= 700) {
            // bomb boom 지우는 함수 사용
            set_Empty(curBOOM->x, curBOOM->y);
            // BOOM 노드 삭제 함수 사용
            if (curBOOM->prev == NULL)
                boomhead->next = curBOOM->next;
            else
                curBOOM->prev->next = curBOOM->next;
            if (curBOOM->next != NULL)
                curBOOM->next->prev = curBOOM->prev;
            free(curBOOM);

        }
        curBOOM = tmpBOOM;
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

