#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include "map.h"
#include "cursor.h" //getcursor, setcursor 함수들을 파일로 따로 뺐음
#include "player.h"

#include "bomb.h"
#include "define_state.h"
#include "Test_Moving.h"
#include "Test_Moving2.h"
#include "Test_Moving3.h"
#include "calculatorDST.h"


unsigned long long start_game_time;
unsigned long long current_game_time;

int player_item_range;

extern BombHead* bombHead;
extern BOOMHead* boomhead;

extern int npcCurPosX, npcCurPosY;
extern int npcCurPosX2, npcCurPosY2;
extern int npcCurPosX3, npcCurPosY3;
extern unsigned long long NPC_current_Time;
extern unsigned long long NPC_current_Time2;
extern unsigned long long NPC_current_Time3;
extern int npc1_state_flag = 0;
extern int npc2_state_flag = 0;
extern int npc3_state_flag = 0;

extern Map_box_head* map_box_head;             //폭탄이 모두 터진 후 박스를 없애기 위한 맵 박스 구조체 배열의 헤드 선언

extern int mapModel[HEIGHT][WIDTH];
extern int mapModel2[HEIGHT][WIDTH];
extern int mapModel3[HEIGHT][WIDTH];



int main(void)
{

	RemoveCursor();

	start_game_time = clock();
	//bombHead1 = makeBombHead();
	//bombHead2 = makeBombHead();

	player_item_range = 1;


	//generateMap();

	bombHead = (BombHead*)malloc(sizeof(bombHead));
	bombHead->next = NULL;
	boomhead = (BOOMHead*)malloc(sizeof(BOOMHead));
	boomhead->next = NULL;


	map_box_head = generate_map_box_head();


	NPC_current_Time = 0;

	for (int game_round = 0; game_round < 3; game_round++)
	{


		PlayerState = 1;
		PlayerCurPosX = arrX_to_cursorX(WIDTH - 3);		//get_Player_starting_point_x();
		PlayerCurPosY = arrY_to_cursorY(HEIGHT - 3);  //get_Player_starting_point_y();

		npcCurPosX = 2 * 2;
		npcCurPosY = 2;

		npcCurPosX2 = 14 * 2;
		npcCurPosY2 = 2;

		npcCurPosX3 = 2 * 2;
		npcCurPosY3 = 14;

		NPC_current_Time = 0;
		NPC_current_Time2 = 0;
		NPC_current_Time3 = 0;

		if (game_round == 1)
		{
			bombHead->next = NULL;
			boomhead->next = NULL;
			TimeCheck();
			TimeCheck_BOOM();
			set_mapModel2();
			set_NPCmapModel();
			SetCurrentCursorPos(3, HEIGHT + GBOARD_ORIGIN_Y);
			printf("                      \n");
			printf("                         \n");
		}
		else if (game_round == 2)
		{
			bombHead->next = NULL;
			boomhead->next = NULL;
			TimeCheck();
			TimeCheck_BOOM();
			set_mapModel3();
			set_NPCmapModel();
			SetCurrentCursorPos(3, HEIGHT + GBOARD_ORIGIN_Y);
			printf("                      \n");
			printf("                         \n");
		}

		drawMaps();

		while (1)
		{
			current_game_time = clock();

			TimeCheck();
			remove_generate_item_all_map_box_struct(map_box_head);
			TimeCheck_BOOM();

			if (CheckPlayerState() == 1)
				Sleep(10000);
			/*if (CheckNPCState() == 1)
			{
				printf("next stage!!!\n");
				Sleep(3000);
				break;
			}*/
			PlayerControl();

			if (CheckPlayerState() == 1)
				Sleep(10000);

			/*NpcMoving();
			NpcMoving2();
			NpcMoving3();*/

			if (game_round == 0) {
				if (CheckNPCState() != 1 && npc1_state_flag == 0) {
					NpcMoving();
				}
				if (npc1_state_flag == 1)
				{
					printf("next stage!!!\n");
					Sleep(3000);
					break;
				}
			}
			npc1_state_flag = 0;
			if (game_round == 1) {
				if (CheckNPCState() != 1 && npc1_state_flag == 0) {
					NpcMoving();
				}
				if (CheckNPCState2() != 1 && npc2_state_flag == 0) {
					NpcMoving2();
				}
				if (npc1_state_flag == 1) {
					NPC1_die();
				}
				if (npc2_state_flag == 1) {
					NPC2_die();
				}
				if (npc1_state_flag == 1 && npc2_state_flag == 1) {
					printf("next stage!!!\n");
					Sleep(3000);
					break;
				}

			}
			npc1_state_flag = 0;
			npc2_state_flag = 0;

			if (game_round == 2) {
				if (CheckNPCState() != 1 && npc1_state_flag == 0) {
					NpcMoving();
				}
				if (CheckNPCState2() != 1 && npc2_state_flag == 0) {
					NpcMoving2();
				}
				if (CheckNPCState3() != 1 && npc3_state_flag == 0) {
					NpcMoving3();
				}
				if (npc1_state_flag == 1) {
					NPC1_die();
				}
				if (npc2_state_flag == 1) {
					NPC2_die();
				}
				if (npc3_state_flag == 1) {
					NPC3_die();
				}
				if (npc1_state_flag == 1 && npc2_state_flag == 1 && npc3_state_flag == 1) {
					printf("next stage!!!\n");
					Sleep(3000);
					break;
				}

			}
		}
	}

	while (1)
	{
		Sleep(10000);
	}

	return (0);
}