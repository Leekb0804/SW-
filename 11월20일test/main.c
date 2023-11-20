#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#include "map.h"
#include "cursor.h"     //getcursor, setcursor 함수들을 파일로 따로 뺐음
#include "player.h"
//#include "bomb.h"
#include "bomb 11-18.h"

#include "Test_Moving.h"
#include "calculatorDST.h"



unsigned long long start_game_time;
unsigned long long current_game_time;

int player_item_range;

extern BombHead* bombHead;
extern BOOMHead* boomhead;

extern int npcCurPosX, npcCurPosY;
extern unsigned long long NPC_current_Time;

int main(void)
{
    RemoveCursor();

    start_game_time = clock();
    //bombHead1 = makeBombHead();
    //bombHead2 = makeBombHead();

    player_item_range = 1;


    generateMap();
    drawMaps();

    PlayerState = 1;
    PlayerCurPosX = get_Player_starting_point_x();
    PlayerCurPosY = 8;  //get_Player_starting_point_y();

    npcCurPosX = 2 * 2;
    npcCurPosY = 2;

    bombHead = (BombHead*)malloc(sizeof(bombHead));
    bombHead->next = NULL;
    boomhead = (BOOMHead*)malloc(sizeof(BOOMHead));
    boomhead->next = NULL;

    NPC_current_Time = 0;

    while (1)
    {
        current_game_time = clock();

        TimeCheck();
        TimeCheck_BOOM();

        if (CheckPlayerState() == 1)
            break;
        if (CheckNPCState() == 1)
            break;

        PlayerControl();
        
        if (CheckPlayerState() == 1)
            break;
        
        NpcMoving();
        
        if (CheckNPCState() == 1)
            break;

        //print_npc_x_y();
    }

    while (1)
        ;
    return (0);
}

