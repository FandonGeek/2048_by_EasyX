#pragma once

#include<stdlib.h>
#include<time.h>	
#include<math.h>
#include<conio.h>
#define ROW 4
#define COL 4	
typedef struct GameInfo
{
	int maxScore;//存储最高分数
	int currentScore;//存储当前分数
	int maxMergeNum;//最大合成数字
	int currentMaxMergeNum; // 现在面上最大的值

	//20221026添加
	int emptyBlock; //空方块数，用以确认游戏是否结束
	int gameOverFlag; //游戏结束标志
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