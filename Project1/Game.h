#pragma once

#include<stdlib.h>
#include<time.h>	
#include<math.h>
#include<conio.h>
#define ROW 4
#define COL 4	
typedef struct GameInfo
{
	int maxScore;//�洢��߷���
	int currentScore;//�洢��ǰ����
	int maxMergeNum;//���ϳ�����
	int currentMaxMergeNum; // ������������ֵ

	//20221026���
	int emptyBlock; //�շ�����������ȷ����Ϸ�Ƿ����
	int gameOverFlag; //��Ϸ������־
}GameInfo;

/*
enum direction
{
	UP, DOWN, LEFT, RIGHT
};
*/

int createNumber();
void mapFillNumber();
void init();
void loadRecord();
void moveUp();
void moveDown();
void moveRight();
void moveLeft();
bool move();
void gameOverCheck();
void gameSave();