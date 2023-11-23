#ifndef __BOMB_11_18_H__
#define __BOMB_11_18_H__

///bomb.h ��������
typedef struct Bomb { //���߿��Ḯ��Ʈ ����ü
	struct Bomb* next;
	struct Bomb* prev;
	unsigned long long start_time; //������ ���� �ð�
	//float time;
	int x;
	int y;
	int len;
}Bomb;

typedef struct BombHead {
	struct Bomb* next;
} BombHead;

typedef struct BOOM {
	struct BOOM* next;
	struct BOOM* prev;
	unsigned long long start_time;
	int x;
	int y;
	int len;
}BOOM;

typedef struct BOOMHead {
	struct BOOM* next;
} BOOMHead;


Bomb* getBombNode(int x, int y);
void insertitem(Bomb* w, int whocall);
BOOM* getnode_BOOM(int x, int y, unsigned long long time);
void insertitem_BOOM(BOOM* w);
void PrintBomb();       ///////////////////// �ʿ��Ѱ�?
void printBOOM();
void BombSwich_On(int x, int y, int whocall);
void TimeCheck();
void TimeCheck_BOOM();
void player_set_bomb();
void npc_set_bomb();


#endif // ! __BOMB_11_18_H__