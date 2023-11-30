#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "map.h"
#include "calculatorDST2.h"
#include "cursor.h"
#include "player.h"

#include "bomb.h"

#include "define_state.h"

int one_srt_dist2[101][101];

int dstX2, dstY2;
int kill_Mode2 = 0;

int visited2[101][101] = { 0, };
int weight2[101][101] = { 0, };

int front2 = 0, rear2 = 0;
int dx2[4] = { 0,1,0,-1 };
int dy2[4] = { 1,0,-1,0 };

int wx2[4] = { 0,1,0,-1 };
int wy2[4] = { 1,0,-1,0 };

Queue2* q;
Queue2* safety;

int can_Pos2 = 0;

void dfs2(int dstX2, int dstY2, int npcX, int npcY) {

	one_srt_dist2[dstY2][dstX2] = 1;
	if (one_srt_dist2[npcY][npcX] == 1) return;
	if (dstX2 + 1 < WIDTH && weight2[dstY2][dstX2 + 1] < weight2[dstY2][dstX2] && one_srt_dist2[dstY2][dstX2 + 1] == 0
		&& weight2[dstY2][dstX2 + 1] != 0) dfs2(dstX2 + 1, dstY2, npcX, npcY);

	if (one_srt_dist2[npcY][npcX] == 1) return;
	if (dstY2 + 1 < HEIGHT && weight2[dstY2 + 1][dstX2] < weight2[dstY2][dstX2] && one_srt_dist2[dstY2 + 1][dstX2] == 0
		&& weight2[dstY2 + 1][dstX2] != 0) dfs2(dstX2, dstY2 + 1, npcX, npcY);

	if (one_srt_dist2[npcY][npcX] == 1) return;
	if (dstX2 - 1 >= 0 && weight2[dstY2][dstX2 - 1] < weight2[dstY2][dstX2] && one_srt_dist2[dstY2][dstX2 - 1] == 0
		&& weight2[dstY2][dstX2 - 1] != 0) dfs2(dstX2 - 1, dstY2, npcX, npcY);

	if (one_srt_dist2[npcY][npcX] == 1) return;
	if (dstY2 - 1 >= 0 && weight2[dstY2 - 1][dstX2] < weight2[dstY2][dstX2] && one_srt_dist2[dstY2 - 1][dstX2] == 0
		&& weight2[dstY2 - 1][dstX2] != 0) dfs2(dstX2, dstY2 - 1, npcX, npcY);

}

void NPCavoidBOMB2(Queue2* safety, int x, int y) {

	rear2++;
	safety[rear2].x = x;
	safety[rear2].y = y;
	safety[rear2].dist = 1;

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			visited2[i][j] = 0;
		}
	}

	while (front2 < rear2) {
		front2++;
		for (int i = 0; i < 4; i++) {
			int nx = safety[front2].x + dx2[i];
			int ny = safety[front2].y + dy2[i];
			if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT) {
				if (visited2[ny][nx] == 0 &&
					mapModel[ny][nx] != STATE_BOMB_SETTING && (
					mapModel[ny][nx] == STATE_EMPTY ||
					mapModel[ny][nx] == STATE_ITEM_BOMB_MAX ||
					mapModel[ny][nx] == STATE_ITEM_BOMB_RANGE ||
					mapModel[ny][nx] == STATE_ITEM_CHARACTER_MOVE ||
					NPCmapModel[ny][nx] == STATE_NPC_WARNING)) {

					rear2++;
					safety[rear2].x = nx;
					safety[rear2].y = ny;
					safety[rear2].dist = safety[front2].dist + 1;
					visited2[ny][nx] = 1;
					weight2[ny][nx] = safety[rear2].dist;

					if (mapModel[ny][nx] == 0 && NPCmapModel[ny][nx] != STATE_NPC_WARNING)
					{
						dstX2 = nx;
						dstY2 = ny;
						return;
					}
				}
			}
		}
	}
}

void bfs2(int x, int y) {

	if (NPCmapModel[y][x] == STATE_NPC_WARNING) {
		kill_Mode2 = 0;
		NPCavoidBOMB2(safety, x, y);
	}

	else {
		rear2++;
		q[rear2].x = x;
		q[rear2].y = y;
		q[rear2].dist = 1;

		while (front2 < rear2) {
			front2++;
			for (int i = 0; i < 4; i++) {
				int nx = q[front2].x + dx2[i];
				int ny = q[front2].y + dy2[i];
				if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT) {
					if (((mapModel[ny][nx] == STATE_EMPTY ||
						mapModel[ny][nx] == STATE_ITEM_BOMB_MAX ||
						mapModel[ny][nx] == STATE_ITEM_BOMB_RANGE ||
						mapModel[ny][nx] == STATE_ITEM_CHARACTER_MOVE) &&
						NPCmapModel[ny][nx] != STATE_NPC_WARNING) &&
						mapModel[ny][nx] != STATE_BOMB_SETTING &&
						visited2[ny][nx] == 0) {

						rear2++;
						q[rear2].x = nx;
						q[rear2].y = ny;
						q[rear2].dist = q[front2].dist + 1;
						visited2[ny][nx] = 1;
						weight2[ny][nx] = q[rear2].dist;


						if (nx * 2 == PlayerCurPosX && ny == PlayerCurPosY) { // 만약 탐색중에 플레이어 위치를 발견하면
							kill_Mode2 = 1;
						}

						if (kill_Mode2 == 1) { // kill_Mode 가 1이면 플레이어만 쫓아다님
							dstX2 = PlayerCurPosX / 2;
							dstY2 = PlayerCurPosY;
						}
						else if (kill_Mode2 == 0) { // 아직 플레이어 위치를 못찾았다면

							int cnt = 0; //여기부터 주석 친 가장 많은 블럭을 부술 수 있는 위치로 가는 알고리즘
							for (int j = 0; j < 4; j++) {
								if (nx + wx2[j] < 0) {
									continue;
								}
								if (nx + wx2[j] >= WIDTH) {
									continue;
								}
								if (ny + wy2[j] < 0) {
									continue;
								}
								if (ny + wy2[j] >= HEIGHT) {
									continue;
								}
								if (mapModel[ny + wy2[j]][nx + wx2[j]] == 1) {
									cnt++;
								}
							}
							if (cnt > can_Pos2) { // 목표 위치를 현재 NPC위치에서 가장 많은 블럭을 부술 수 있는 위치로 설정함
								can_Pos2 = cnt;
								dstX2 = nx;
								dstY2 = ny;
							}
						}
					}
				}
			}
		}
	}
}

int ShortestDistance2(int npcX, int npcY) {

	static int flag2 = 0;

	if (flag2 == 0)
	{
		q = (Queue2*)calloc(((WIDTH * 2) * (HEIGHT * 2)), sizeof(Queue2));
		safety = (Queue2*)calloc(((WIDTH * 2) * (HEIGHT * 2)), sizeof(Queue2));
		flag2++;
	}
	else
	{
		memset(q, 0, sizeof(q));
		memset(safety, 0, sizeof(safety));
	}

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			one_srt_dist2[i][j] = 0;
			weight2[i][j] = 0;
			visited2[i][j] = 0;
		}
	}
	
	front2 = rear2 = 0;
	can_Pos2 = 0;				// 
	weight2[npcY][npcX] = 0;

	bfs2(npcX, npcY); // 여기에 NPC의 출발(x,y)좌표를 집어넣는다.

	weight2[npcY][npcX] = 1;
	int dist = q[rear2].dist;

	dfs2(dstX2, dstY2, npcX, npcY);

	//지금 one_srt_dist에서 문제가 생김

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (weight2[i][j] == 0) {
				one_srt_dist2[i][j] = -1;
			}
			if (weight2[i][j] == 0 && mapModel[i][j] == 0) {
				one_srt_dist2[i][j] = 0;
			}
		}
	}

	return kill_Mode2;
}