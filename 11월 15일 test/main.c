#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#include "block.h"
#include "map.h"
#include "cursor.h"     //getcursor, setcursor 함수들을 파일로 따로 뺐음
#include "player.h"
#include "bomb.h"
#include "Test_Moving.h"
#include "calculatorDST.h"




#include "debug.h"

unsigned long long start_game_time;
unsigned long long current_game_time;

BombHead* bombHead1;
BombHead* bombHead2;

int player_item_range;

extern BombHead* bombHead;

extern int npcCurPosX, npcCurPosY;

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
    bombHead->head = NULL;

    while (1)
    {
        current_game_time = clock();

        TimeCheck();

        if (CheckPlayerState() == 1)
            return (0);
        if (CheckNPCState() == 1)
            return (0);
        Sleep(10);
        PlayerControl();
        if (CheckPlayerState() == 1)
            return (0);
        NpcMoving();
        if (CheckNPCState() == 1)
            return (0);

        //print_npc_x_y();
    }

    return (0);
}

