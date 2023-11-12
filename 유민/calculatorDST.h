#ifndef __CALCULATORDST_H__
#define __CALCULATORDST_H__
#define _CRT_SECURE_NO_WARNINGS

#include "LeeGB_map.h"

extern int one_srt_dist[101][101];
extern int dstX, dstY;
extern int visited[101][101];
extern int weight[101][101];

typedef struct queue {	//BFS 탐색에 쓰일 큐
	int x;
	int y;
	int dist;
}Queue;

void bfs(Queue* q, int x, int y); // BFS탐색, 목적지까지의 최단거리를 구해줌
void dfs(int x, int y, int npcX, int npcY); // DFS로 one_srt_dist 배열 완성
int ShortestDistance(int npcX, int npcY);

#endif
