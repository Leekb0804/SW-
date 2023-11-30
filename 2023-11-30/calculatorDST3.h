#ifndef __CALCULATORDST3_H__
#define __CALCULATORDST3_H__
#define _CRT_SECURE_NO_WARNINGS

#include "map.h"

extern int one_srt_dist3[101][101];
extern int dstX3, dstY3;
extern int visited3[101][101];
extern int weight3[101][101];
extern int kill_Mode3;

typedef struct queue3 {
	int x;
	int y;
	int dist;
}Queue3;

void bfs3(int x, int y);
void dfs3(int x, int y, int npcX, int npcY);
int ShortestDistance3(int npcX, int npcY);

#endif