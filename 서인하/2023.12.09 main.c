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
#include "calculatorDST2.h"
#include "calculatorDST3.h"
#include "stage_image.h"


int npc2_Life_flag = 1;
int npc3_Life_flag = 2;
static int npc_speed_phase = 0;

unsigned long long start_game_time;

unsigned long long current_game_time;
unsigned long long stage_start_time;

int player_item_range;

extern BombHead* bombHead;
extern BOOMHead* boomhead;

int npcCurPosX, npcCurPosY;
int npcCurPosX2, npcCurPosY2;
int npcCurPosX3, npcCurPosY3;
unsigned long long NPC_current_Time;
unsigned long long NPC_current_Time2;
unsigned long long NPC_current_Time3;
int npc1_state_flag = 0;
int npc2_state_flag = 0;
int npc3_state_flag = 0;

extern Map_box_head* map_box_head;             //폭탄이 모두 터진 후 박스를 없애기 위한 맵 박스 구조체 배열의 헤드 선언

extern int mapModel[HEIGHT][WIDTH];
extern int mapModel2[HEIGHT][WIDTH];
extern int mapModel3[HEIGHT][WIDTH];

extern int bomb_max;
extern int player_bomb_len;
extern int player_move;

int game_round;

int main(void)
{
	q3 = (Queue3*)calloc(((WIDTH * 1) * (HEIGHT * 1)), sizeof(Queue3));
	safety3 = (Queue3*)calloc(((WIDTH * 1) * (HEIGHT * 1)), sizeof(Queue3));

	q2 = (Queue2*)calloc(((WIDTH * 1) * (HEIGHT * 1)), sizeof(Queue2));
	safety2 = (Queue2*)calloc(((WIDTH * 1) * (HEIGHT * 1)), sizeof(Queue2));

	q = (Queue*)calloc(((WIDTH * 1) * (HEIGHT * 1)), sizeof(Queue));
	safety = (Queue*)calloc(((WIDTH * 1) * (HEIGHT * 1)), sizeof(Queue));

	Sleep(500);

	system("mode con:cols=100 lines=40 | title 포포폭탄");

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

	for (game_round = 0; game_round < 6; game_round++)
	{
		bomb_max = 1;
		player_bomb_len = 1;
		player_move = 1;
		stage_start_time = clock();
		PlayerState = 1;
		PlayerCurPosX = arrX_to_cursorX(WIDTH - 3);		//get_Player_starting_point_x();
		PlayerCurPosY = arrY_to_cursorY(HEIGHT - 3);  //get_Player_starting_point_y();

		npcCurPosX = 2 * 2 + GBOARD_ORIGIN_X;
		npcCurPosY = 2 + GBOARD_ORIGIN_Y;

		npcCurPosX2 = 14 * 2 + GBOARD_ORIGIN_X;
		npcCurPosY2 = 2 + GBOARD_ORIGIN_Y;

		npcCurPosX3 = 2 * 2 + +GBOARD_ORIGIN_X;
		npcCurPosY3 = 14 + +GBOARD_ORIGIN_Y;

		NPC_current_Time = 0;
		NPC_current_Time2 = 0;
		NPC_current_Time3 = 0;


		npc1_state_flag = 0;
		npc2_state_flag = 0;
		npc3_state_flag = 0;

		npc2_Life_flag = 1;
		npc3_Life_flag = 2;
		if (game_round >= 3) {
			npc_speed_phase = 1;
		}

		if (game_round == 0)
		{

			bombHead->next = NULL;
			boomhead->next = NULL;
			/*TimeCheck();
			TimeCheck_BOOM();*/
			set_mapModel_spiral();
			reset_npcMapModel();
			draw_Stagemap_reset();
			NextStage_Mapdrawing();
			draw_Stagemap_reset();
			SetCurrentCursorPos(3, HEIGHT + GBOARD_ORIGIN_Y);
			printf("                      \n");
			printf("                         \n");
		}
		else if (game_round == 1)
		{
			bombHead->next = NULL;
			boomhead->next = NULL;
			TimeCheck();
			TimeCheck_BOOM();
			set_mapModel_eye();
			reset_npcMapModel();
			draw_Stagemap_reset();
			NextStage_Mapdrawing();
			draw_Stagemap_reset();
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
			set_mapModel_snail();
			reset_npcMapModel();
			draw_Stagemap_reset();
			NextStage_Mapdrawing();
			draw_Stagemap_reset();
			SetCurrentCursorPos(3, HEIGHT + GBOARD_ORIGIN_Y);
			printf("                      \n");
			printf("                         \n");
		}
		else if (game_round == 3)
		{
			bombHead->next = NULL;
			boomhead->next = NULL;
			TimeCheck();
			TimeCheck_BOOM();
			set_mapModel_symmetry();
			reset_npcMapModel();
			draw_Stagemap_reset();
			NextStage_Mapdrawing();
			draw_Stagemap_reset();
			SetCurrentCursorPos(3, HEIGHT + GBOARD_ORIGIN_Y);
			printf("                      \n");
			printf("                         \n");
		}
		else if (game_round == 4)
		{
			bombHead->next = NULL;
			boomhead->next = NULL;
			TimeCheck();
			TimeCheck_BOOM();
			set_mapModel_popopoktan();
			reset_npcMapModel();
			draw_Stagemap_reset();
			NextStage_Mapdrawing();
			draw_Stagemap_reset();
			SetCurrentCursorPos(3, HEIGHT + GBOARD_ORIGIN_Y);
			printf("                      \n");
			printf("                         \n");
		}
		else if (game_round == 5)
		{
			bombHead->next = NULL;
			boomhead->next = NULL;
			TimeCheck();
			TimeCheck_BOOM();
			set_mapModel_firework();
			reset_npcMapModel();
			draw_Stagemap_reset();
			NextStage_Mapdrawing();
			draw_Stagemap_reset();
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

			if (CheckPlayerState() == 1) {
				Sleep(10000);
			}
			PlayerControl();
			Explain();

			if (game_round == 0) {
				if (CheckNPCState() != 1 && npc1_state_flag == 0) {
					NpcMoving(npc_speed_phase);
				}
				if (npc1_state_flag == 1)
				{
					//printf("next stage!!!\n");
					Sleep(3000);
					break;
				}
			}
			else if (game_round == 1) {
				if (npc1_state_flag == 0 && CheckNPCState() != 1) {
					NpcMoving(npc_speed_phase);
				}
				if (npc2_state_flag == 0 && CheckNPCState2() != 1) {
					NpcMoving2(npc_speed_phase);
				}
				if (npc1_state_flag == 1) {
					NPC1_die();
				}
				if (npc2_state_flag == 1) {
					if (npc2_Life_flag > 0) {
						npcCurPosX2 = 14 * 2 + GBOARD_ORIGIN_X;
						npcCurPosY2 = 2 + GBOARD_ORIGIN_Y;
						npc2_Life_flag--;
						npc2_state_flag = 0;
					}
					else {
						NPC2_die();
					}
				}
				if (npc1_state_flag == 1 && npc2_state_flag == 1) {
					//printf("next stage!!!\n");
					Sleep(3000);
					break;
				}
			}
			else if (game_round == 2) {
				if (CheckNPCState() != 1 && npc1_state_flag == 0) {
					NpcMoving(npc_speed_phase);
				}
				if (CheckNPCState2() != 1 && npc2_state_flag == 0) {
					NpcMoving2(npc_speed_phase);
				}
				if (CheckNPCState3() != 1 && npc3_state_flag == 0) {
					NpcMoving3(npc_speed_phase);
				}
				if (npc1_state_flag == 1) {
					NPC1_die();
				}
				if (npc2_state_flag == 1) {
					if (npc2_Life_flag > 0) {
						npcCurPosX2 = 14 * 2 + GBOARD_ORIGIN_X;
						npcCurPosY2 = 2 + GBOARD_ORIGIN_Y;
						npc2_Life_flag--;
						npc2_state_flag = 0;
					}
				}
				if (npc3_state_flag == 1) {
					if (npc3_Life_flag > 0) {
						npcCurPosX3 = 2 * 2 + +GBOARD_ORIGIN_X;
						npcCurPosY3 = 14 + +GBOARD_ORIGIN_Y;
						npc3_Life_flag--;
						npc3_state_flag = 0;
					}
					else {
						NPC3_die();
					}
				}
				if (npc1_state_flag == 1 && npc2_state_flag == 1 && npc3_state_flag == 1) {
					//printf("next stage!!!\n");

					Sleep(3000);
					break;
				}
			}
			else if (game_round == 3) {
				if (CheckNPCState() != 1 && npc1_state_flag == 0) {
					NpcMoving(npc_speed_phase);
				}
				if (npc1_state_flag == 1)
				{
					//printf("next stage!!!\n");
					Sleep(3000);
					break;
				}
			}
			else if (game_round == 4) {
				if (CheckNPCState() != 1 && npc1_state_flag == 0) {
					NpcMoving(npc_speed_phase);
				}
				if (CheckNPCState2() != 1 && npc2_state_flag == 0) {
					NpcMoving2(npc_speed_phase);
				}
				if (npc1_state_flag == 1) {
					NPC1_die();
				}
				if (npc2_state_flag == 1) {
					if (npc2_Life_flag > 0) {
						npcCurPosX2 = 14 * 2 + GBOARD_ORIGIN_X;
						npcCurPosY2 = 2 + GBOARD_ORIGIN_Y;
						npc2_Life_flag--;
						npc2_state_flag = 0;
					}
					else {
						NPC2_die();
					}
				}
				if (npc1_state_flag == 1 && npc2_state_flag == 1) {
					Sleep(3000);
					break;
				}
			}
			else if (game_round == 5) {
				if (CheckNPCState() != 1 && npc1_state_flag == 0) {
					NpcMoving(npc_speed_phase);
				}
				if (CheckNPCState2() != 1 && npc2_state_flag == 0) {
					NpcMoving2(npc_speed_phase);
				}
				if (CheckNPCState3() != 1 && npc3_state_flag == 0) {
					NpcMoving3(npc_speed_phase);
				}
				if (npc1_state_flag == 1) {
					NPC1_die();
				}
				if (npc2_state_flag == 1) {
					if (npc2_Life_flag > 0) {
						npcCurPosX2 = 14 * 2 + GBOARD_ORIGIN_X;
						npcCurPosY2 = 2 + GBOARD_ORIGIN_Y;
						npc2_Life_flag--;
						npc2_state_flag = 0;
					}
					else {
						NPC2_die();
					}
				}
				if (npc3_state_flag == 1) {
					if (npc3_Life_flag > 0) {
						npcCurPosX3 = 2 * 2 + +GBOARD_ORIGIN_X;
						npcCurPosY3 = 14 + +GBOARD_ORIGIN_Y;
						npc3_Life_flag--;
						npc3_state_flag = 0;
					}
					else {
						NPC3_die();
					}
				}
				if (npc1_state_flag == 1 && npc2_state_flag == 1 && npc3_state_flag == 1) {

					Sleep(3000);
					break;
				}
			}

			/*SetCurrentCursorPos(0 + GBOARD_ORIGIN_X, 23 + GBOARD_ORIGIN_Y);
			for (int i = 0; i < HEIGHT; i++) {
				for (int j = 0; j < WIDTH; j++) {
					printf("%4d", mapModel[i][j]);
				}
				printf("\n");
			}*/

			if (game_round >= 3) {
				sky_bomb_drop();
				
			}
		}
	}
	Clear_Letterdrawing();
	while (1)
	{
		Sleep(10000);
	}

	return (0);
}
