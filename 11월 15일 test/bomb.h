#ifndef __BOMB_H__
#define __BOMB_H__

typedef struct Bomb { //이중연결리스트 구조체
    struct Bomb* next;
    struct Bomb* prev;
    unsigned long long start_time; //생성시 게임 시간
    //float time;
    int x;
    int y;
}Bomb;

typedef struct BombHead {
    struct Bomb* head;
} BombHead;


//Bomb* makeBombHead();               //Bomb 구조체의 헤드 만들어서 반환
//Bomb* getBombNode(int x, int y);    //Bomb 구조체 만들기
//void insertBomb(Bomb* w);           //Bomb 구조체 배열에 Bomb w노드 삽입
//void Bomb_TimeCheck();              //Bomb 이 터질시간이 되었는지 체크
//void ﻿BombSwich_On(int x, int y);
//void player_set_bomb();


void TimeCheck();
Bomb* getBombNode(int x, int y);
void insertitem(Bomb* w);
void PrintBomb();
void ProcessKeyInput();
void ﻿BombSwich_On(int x, int y);
BombHead* init_List();
void player_set_bomb();

#endif