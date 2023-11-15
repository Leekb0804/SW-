//#include "bomb.h"
//#include "map.h"
//#include "define_state.h"
//
//
//#include <stdlib.h>
//
//extern int mapModel[HEIGHT][WIDTH];
//
//extern int player_item_range;       //main에서 선언된 변수 사용
//extern BombHead* bombHead1;         //main에서 선언된 변수 사용
//
//
//Bomb* makeBombHead()
//{
//	BombHead* newHead = (BombHead*)malloc(sizeof(BombHead));
//	newHead->next = NULL;
//
//	return (newHead);
//}
//
//Bomb* getBombNode(int x, int y)
//{
//    Bomb* newbomb = (Bomb*)malloc(sizeof(Bomb));
//    newbomb->next = NULL;
//    newbomb->start_time = clock(); // 현재 시간으로 초기화
//    //newbomb->time = 0;
//    newbomb->x = x;
//    newbomb->y = y;
//    newbomb->bomb_range = player_item_range;
//    return newbomb;
//}
//
//void insertBomb(Bomb* w)
//{
//    if (bombHead1->next == NULL) {
//        bombHead1->next = w;
//        return;
//    }
//
//    Bomb* curBomb = bombHead1->next;
//    while (curBomb->next != NULL) {
//        //if (curBomb->x == w->x && curBomb->y == w->y) return //이미 물풍선이 있는 곳에 또 물풍선을 놓으려고 하면 리턴
//        curBomb = curBomb->next;
//    }
//    curBomb->next = w;
//    
//    set_Bomb(w->x, w->y);
//}
//
//void Bomb_TimeCheck()
//{
//    if (bombHead1->next == NULL) return;
//    Bomb* curBomb = bombHead1->next;
//    while (curBomb != NULL) {
//        unsigned long long curtime = clock();
//        if (curtime - curBomb->start_time >= 3000)          //3초가 지났으면 물풍선 폭파
//        {
//            //﻿//BombSwich_On(curBomb->x, curBomb->y);
//            ////여기에 맵 다시 그려야함. to 경빈이에게
//        }
//        curBomb = curBomb->next;
//    }
//}
//
////void ﻿BombSwich_On(int x, int y)
////{
////    if (bombHead1->next == NULL) return;
////    Bomb* curBomb = bombHead1->next;
////    Bomb* PBpmb = curBomb;
////    
////
////    // 왜 PBpmb 를 사용하는지? curBomb->x == x 면 while문 종료시키면 되는거 아닌지? 그리고 이 BombSwitch_On함수의 인자로 TimeCheck의 curBomb이 들어가면 되는거 아닌지?
//    //while (curBomb != NULL) {
//    //    if (curBomb->next->x == x && curBomb->next->y == y) {
//    //        PBpmb = curBomb;
//    //    }
//    //    curBomb = curBomb->next;
//    //}
////
////    Bomb* temp = PBpmb->next;
////    mapModel[temp->y][temp->x] == 0; //맵 정보 수정. 물풍선 있던 자리에 아무것도 출력하지 않음.
////    
////    set_Empty(temp->x, temp->y);        ///////////////////////////////////////////////////////추가
////    
////    PBpmb->next = PBpmb->next->next;
////    free(temp);
////    printf("%d %d BOMB!!!\n", x, y);
////
////    for (int i = -bomb_len; i <= bomb_len; i++) { //폭탄이 터지는 범위 훑기
////        if (i == 0) continue;
////        int m = i + y;
////        int n = i + x;
////
////        //세로줄 확인
////        if (m < 0 || 8 < m) continue; //맵밖으로 벗어나면 continue
////        if (mapModel[m][x] == 1) { //나무 상자라면
////            mapModel[m][x] == 0; //나무 상자 파괴
////            //여기에 아이템 랜덤 드랍 함수. to 경빈이에게
////        }
////        if (mapModel[m][x] == 111 || mapModel[m][x] == 222 || mapModel[m][x] == 333) { //아이템이 있다면
////            mapModel[m][x] == 0; //아이템 파괴
////        }
////        else if (mapModel[m][x] == 2) { //2가 플레이어라고 가정. 만약 플레이어라면
////            GameOver = 1; //게임 오버.
////            //게임 오버 함수가 있다면 호출. to 경빈이에게
////        }
////        else if (mapModel[m][x] == 3) { //3이 적이라고 가정. 만약 적이라면
////            printf("next stage!");
////            //다음 스테이지 함수 호출. to 경빈이에게
////        }
////        else if (mapModel[m][x] == 400) { //만약 다른 폭탄이 있다면
////            ﻿BombSwich_On(x, m); //재귀호출
////        }
////
////        //가로줄 확인
////        if (n < 0 || 8 < n) continue; //맵밖으로 벗어나면 continue
////        if (mapModel[y][n] == 1) { //나무 상자라면
////            mapModel[y][n] == 0; //나무 상자 파괴
////            //여기에 아이템 랜덤 드랍 함수. to 경빈이에게
////        }
////        if (mapModel[y][n] == 111 || mapModel[y][n] == 222 || mapModel[y][n] == 333) { //아이템이 있다면
////            mapModel[y][n] == 0; //아이템 파괴
////        }
////        else if (mapModel[y][n] == 2) { //2가 플레이어라고 가정. 만약 플레이어라면
////            GameOver = 1; //게임 오버.
////            printf("GameOver");
////            //게임 오버 함수가 있다면 호출. to 경빈이에게
////        }
////        else if (mapModel[y][n] == 3) { //3이 적이라고 가정. 만약 적이라면
////            printf("next stage!");
////            //다음 스테이지 함수 호출. to 경빈이에게
////        }
////        else if (mapModel[y][n] == 400) { //만약 다른 폭탄이 있다면
////            ﻿BombSwich_On(n, y); //재귀호출
////        }
////    }
////
////}