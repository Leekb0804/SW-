#ifndef __CALCULATORDST2_H__
#define __CALCULATORDST2_H__
#define _CRT_SECURE_NO_WARNINGS

#include "map.h"

extern int one_srt_dist2[101][101];
extern int dstX2, dstY2;
extern int visited2[101][101];
extern int weight2[101][101];
extern int kill_Mode2;

typedef struct queue2 {
	int x;
	int y;
	int dist;
}Queue2;

void bfs2(int x, int y);
void dfs2(int x, int y, int npcX, int npcY);
int ShortestDistance2(int npcX, int npcY);

#endif