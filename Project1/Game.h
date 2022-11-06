#pragma once

#include<stdlib.h>
#include<time.h>	
#include<math.h>
#include<conio.h>

#define ROW 4
#define COL 4	

//�����
enum direction
{
	UP, DOWN, LEFT, RIGHT
};

//��Ϸ��Ϣ
typedef struct GameInfo
{
	int maxScore;//�洢��߷���
	int currentScore;//�洢��ǰ����
	int maxMergeNum;//���ϳ�����
	int currentMaxMergeNum; // ������������ֵ
	int emptyBlock; //�շ�����������ȷ����Ϸ�Ƿ����
	int gameOverFlag; //��Ϸ������־
}GameInfo;

int createNumber();
void mapFillNumber();
void init();
void loadRecord();
void ScoreCalculation(int MergeNum);
bool isChanged();
void copyData();
void moveUp();
void moveDown();
void moveRight();
void moveLeft();
bool move(direction dir);
void gameOverCheck();
void gameSave();