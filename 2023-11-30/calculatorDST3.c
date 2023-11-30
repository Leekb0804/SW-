#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "map.h"
#include "calculatorDST3.h"
#include "cursor.h"
#include "player.h"

#include "bomb.h"

#include "define_state.h"

int one_srt_dist3[101][101];

int dstX3, dstY3;
int kill_Mode3 = 0;

int visited3[101][101] = { 0, };
int weight3[101][101] = { 0, };

int front3 = 0, rear3 = 0;
int dx3[4] = { 0,1,0,-1 };
int dy3[4] = { 1,0,-1,0 };

int wx3[4] = { 0,1,0,-1 };
int wy3[4] = { 1,0,-1,0 };

Queue3* q;
Queue3* safety;

int can_Pos3 = 0;

void dfs3(int dstX3, int dstY3, int npcX, int npcY) {

	one_srt_dist3[dstY3][dstX3] = 1;

	if (one_srt_dist3[npcY][npcX] == 1) return;
	if (dstX3 - 1 >= 0 && weight3[dstY3][dstX3 - 1] < weight3[dstY3][dstX3] && one_srt_dist3[dstY3][dstX3 - 1] == 0
		&& weight3[dstY3][dstX3 - 1] != 0) dfs3(dstX3 - 1, dstY3, npcX, npcY);

	if (one_srt_dist3[npcY][npcX] == 1) return;
	if (dstY3 - 1 >= 0 && weight3[dstY3 - 1][dstX3] < weight3[dstY3][dstX3] && one_srt_dist3[dstY3 - 1][dstX3] == 0
		&& weight3[dstY3 - 1][dstX3] != 0) dfs3(dstX3, dstY3 - 1, npcX, npcY);

	if (one_srt_dist3[npcY][npcX] == 1) return;
	if (dstX3 + 1 < WIDTH && weight3[dstY3][dstX3 + 1] < weight3[dstY3][dstX3] && one_srt_dist3[dstY3][dstX3 + 1] == 0
		&& weight3[dstY3][dstX3 + 1] != 0) dfs3(dstX3 + 1, dstY3, npcX, npcY);

	if (one_srt_dist3[npcY][npcX] == 1) return;
	if (dstY3 + 1 < HEIGHT && weight3[dstY3 + 1][dstX3] < weight3[dstY3][dstX3] && one_srt_dist3[dstY3 + 1][dstX3] == 0
		&& weight3[dstY3 + 1][dstX3] != 0) dfs3(dstX3, dstY3 + 1, npcX, npcY);

}

void NPCavoidBOMB3(Queue3* safety, int x, int y) {

	rear3++;
	safety[rear3].x = x;
	safety[rear3].y = y;
	safety[rear3].dist = 1;

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			visited3[i][j] = 0;
		}
	}

	while (front3 < rear3) {
		front3++;
		for (int i = 0; i < 4; i++) {
			int nx = safety[front3].x + dx3[i];
			int ny = safety[front3].y + dy3[i];
			if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT) {
				if (visited3[ny][nx] == 0 &&
					mapModel[ny][nx] != STATE_BOMB_SETTING && 
					mapModel[ny][nx] != STATE_BOX && (
					mapModel[ny][nx] == STATE_EMPTY ||
					mapModel[ny][nx] == STATE_ITEM_BOMB_MAX ||
					mapModel[ny][nx] == STATE_ITEM_BOMB_RANGE ||
					mapModel[ny][nx] == STATE_ITEM_CHARACTER_MOVE ||
					NPCmapModel[ny][nx] == STATE_NPC_WARNING)) {

					rear3++;
					safety[rear3].x = nx;
					safety[rear3].y = ny;
					safety[rear3].dist = safety[front3].dist + 1;
					visited3[ny][nx] = 1;
					weight3[ny][nx] = safety[rear3].dist;

					if (mapModel[ny][nx] == 0 && NPCmapModel[ny][nx] != STATE_NPC_WARNING)
					{
						dstX3 = nx;
						dstY3 = ny;
						return;
					}
				}
			}
		}
	}
}

void bfs3(int x, int y) {

	if (NPCmapModel[y][x] == STATE_NPC_WARNING) {
		kill_Mode3 = 0;
		NPCavoidBOMB3(safety, x, y);
	}

	else {
		rear3++;
		q[rear3].x = x;
		q[rear3].y = y;
		q[rear3].dist = 1;

		while (front3 < rear3) {
			front3++;
			for (int i = 0; i < 4; i++) {
				int nx = q[front3].x + dx3[i];
				int ny = q[front3].y + dy3[i];
				if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT) {
					if (((mapModel[ny][nx] == STATE_EMPTY || // 아이템 무시하고 가도록, 나중에 STATE_ITEM_EXIST로 한번에 비교
						mapModel[ny][nx] == STATE_ITEM_BOMB_MAX ||
						mapModel[ny][nx] == STATE_ITEM_BOMB_RANGE ||
						mapModel[ny][nx] == STATE_ITEM_CHARACTER_MOVE) &&
						NPCmapModel[ny][nx] != STATE_NPC_WARNING) &&
						mapModel[ny][nx] != STATE_BOMB_SETTING &&
						mapModel[ny][nx] != STATE_BOX &&
						visited3[ny][nx] == 0) {

						rear3++;
						q[rear3].x = nx;
						q[rear3].y = ny;
						q[rear3].dist = q[front3].dist + 1;
						visited3[ny][nx] = 1;
						weight3[ny][nx] = q[rear3].dist;


						if (nx * 2 == PlayerCurPosX && ny == PlayerCurPosY) { // 만약 탐색중에 플레이어 위치를 발견하면
							kill_Mode3 = 1;
						}

						if (kill_Mode3 == 1) { // kill_Mode 가 1이면 플레이어만 쫓아다님
							dstX3 = PlayerCurPosX / 2;
							dstY3 = PlayerCurPosY;
						}
						else if (kill_Mode3 == 0) { // 아직 플레이어 위치를 못찾았다면

							int cnt = 0; //여기부터 주석 친 가장 많은 블럭을 부술 수 있는 위치로 가는 알고리즘
							for (int j = 0; j < 4; j++) {
								if (nx + wx3[j] < 0) {
									continue;
								}
								if (nx + wx3[j] >= WIDTH) {
									continue;
								}
								if (ny + wy3[j] < 0) {
									continue;
								}
								if (ny + wy3[j] >= HEIGHT) {
									continue;
								}
								if (mapModel[ny + wy3[j]][nx + wx3[j]] == 1) {
									cnt++;
								}
							}
							if (cnt > can_Pos3) { // 목표 위치를 현재 NPC위치에서 가장 많은 블럭을 부술 수 있는 위치로 설정함
								can_Pos3 = cnt;
								dstX3 = nx;
								dstY3 = ny;
							}
						}
					}
				}
			}
		}
	}
}

int ShortestDistance3(int npcX, int npcY) {

	static int flag3 = 0;

	if (flag3 == 0)
	{
		q = (Queue3*)calloc(((WIDTH * 2) * (HEIGHT * 2)), sizeof(Queue3));
		safety = (Queue3*)calloc(((WIDTH * 2) * (HEIGHT * 2)), sizeof(Queue3));
		flag3++;
	}
	else
	{
		memset(q, 0, sizeof(q));
		memset(safety, 0, sizeof(safety));
	}

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			one_srt_dist3[i][j] = 0;
			weight3[i][j] = 0;
			visited3[i][j] = 0;
		}
	}

	front3 = rear3 = 0;
	can_Pos3 = 0;				// 
	weight3[npcY][npcX] = 0;

	bfs3(npcX, npcY); // 여기에 NPC의 출발(x,y)좌표를 집어넣는다.

	weight3[npcY][npcX] = 1;
	int dist = q[rear3].dist;

	dfs3(dstX3, dstY3, npcX, npcY);

	//지금 one_srt_dist에서 문제가 생김

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (weight3[i][j] == 0) {
				one_srt_dist3[i][j] = -1;
			}
			if (weight3[i][j] == 0 && mapModel[i][j] == 0) {
				one_srt_dist3[i][j] = 0;
			}
		}
	}

	return kill_Mode3;
}