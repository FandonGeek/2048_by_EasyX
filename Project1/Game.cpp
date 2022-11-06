#include"Game.h"
#include <stdio.h>
#include<string.h>

//存储数据的数组&运行格子
int map[ROW][COL];

//存储移动前数据的格子，移动判断和动画所用
int map_old[ROW][COL];

//是否生成一个数字
int movedflag = 0; 

//游戏运行数值组
GameInfo gameInfo;

//读取文件函数
void loadRecord() {
	FILE* recordReader;
	errno_t err = fopen_s(&recordReader, "recordfile.dat", "r");
	if (err != 0 || recordReader == NULL) {
		init();
		return;
	}
	int topScore, currentScore, maxNum, currentMaxNum;
	if (fscanf_s(recordReader, "top_score:%d current_score:%d maxNum:%d current_maxNum:%d", &topScore, &currentScore, &maxNum, &currentMaxNum) != 4) {
		fclose(recordReader);
		init();
		return;
	}

	gameInfo.maxScore = topScore;
	gameInfo.currentScore = currentScore;
	gameInfo.maxMergeNum = maxNum;
	gameInfo.currentMaxMergeNum = currentMaxNum;
	gameInfo.emptyBlock = 16;

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			int readInCount = fscanf_s(recordReader, "%d", &map[i][j]);
			// 读取数据出错或者数据无效
			if ((readInCount != 1) || (map[i][j] < 0) || (4096 <= map[i][j])) {
				fclose(recordReader);
				init();
				return;
			}
			if (map[i][j] != 0)
				gameInfo.emptyBlock--;
		}
	}
	gameOverCheck();
	fclose(recordReader);
}

//随机产生2or4 2的概率更高
int createNumber()
{
	if (rand() % 10 != 0)
	{
		return  2;
	}
	else
	{
		return 4;
	}
}

//给数组空白处填充一个数
//20221028重写
void mapFillNumber()
{
	if (gameInfo.emptyBlock == 0)
		return;
	int r = rand() % gameInfo.emptyBlock;
	gameInfo.emptyBlock--;
	int* p = &map[0][0]-1, i = 0;
	do {
		while (*++p);
	} while (i++<r);

	*p = createNumber();
}

//初始化或者游戏重启的函数
void init()
{
	//面板置0初始化
	memset(map, 0, sizeof(int) * 16);
	//设置随机数种子
	srand((unsigned int)time(NULL));

	//游戏重启
	gameInfo.gameOverFlag = 0;

	//现有值置0
	gameInfo.currentMaxMergeNum = 2;
	gameInfo.currentScore = 0;
	gameInfo.emptyBlock = 16;

	//随机产生一个数，并且放到数组里面去 map[?][?] = createNumber();
	for (int i = 0; i < 2; i++)
	{
		mapFillNumber();
	}
	
}

void copyData() {
	int i, j;
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++)
			map_old[i][j] = map[i][j];
}

//分数、最高合成数和空余格子数计算器
void ScoreCalculation(int MergeNum) {
	//20221028加入
	gameInfo.emptyBlock++;

	if (MergeNum > gameInfo.maxMergeNum) {
		gameInfo.currentMaxMergeNum = MergeNum;
		gameInfo.maxMergeNum = MergeNum;
	}
	else if (MergeNum > gameInfo.currentMaxMergeNum) {
		gameInfo.currentMaxMergeNum = MergeNum;
	}
	gameInfo.currentScore += MergeNum;
	if (gameInfo.currentScore > gameInfo.maxScore) {
		gameInfo.maxScore = gameInfo.currentScore;
	}
}

//是否有移动的判断函数，决定movedflag的值
bool isChanged()//检查数据是否（变化/移动） 
{
	int i, j;
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++)
			if (map_old[i][j] != map[i][j])
				return true;
	return false;
}

//向上移动
void moveUp()
{
	/*
	向上移动:遍历每列
	*/
	for (int i = 0; i < COL; i++)
	{
		int temp = 0;
		for (int begin = 1; begin < ROW; begin++)
		{
			if (map[begin][i] != 0)
			{
				if (map[temp][i] == 0)
				{
					map[temp][i] = map[begin][i];
					map[begin][i] = 0;
				}
				else if (map[temp][i] == map[begin][i])
				{
					map[temp][i] += map[begin][i];
					//计分
					ScoreCalculation(map[temp][i]);
					map[begin][i] = 0;
					temp++;
				}
				else
				{
					map[temp + 1][i] = map[begin][i];
					if (temp + 1 != begin)//如果temp+1和begn不在同一个位置,就让begin所在的位置的数字置空
					{
						map[begin][i] = 0;
					}
					temp++;
				}
				if (isChanged()) {
					movedflag = 1;
				}
			}
		}
	}
}
//向下移动
void moveDown()
{
	for (int i = 0; i < COL; i++)
	{
		if (gameInfo.gameOverFlag == 1) {
			break;
		}
		int temp = ROW - 1;
		for (int begin = ROW - 2; begin >= 0; begin--)
		{
			if (map[begin][i] != 0)
			{
				if (map[temp][i] == 0)
				{
					map[temp][i] = map[begin][i];
					map[begin][i] = 0;
				}
				else if (map[temp][i] == map[begin][i])
				{
					map[temp][i] += map[begin][i];
					//计分
					ScoreCalculation(map[temp][i]);
					map[begin][i] = 0;
					temp--;
				}
				else
				{
					map[temp - 1][i] = map[begin][i];
					if ((temp - 1) != begin)
					{
						map[begin][i] = 0;
					}
					temp--;
				}
				if (isChanged()) {
					movedflag = 1;
				}
			}
		}
	}
}
//向左移动
void moveLeft()
{
	for (int i = 0; i < COL; i++)
	{
		if (gameInfo.gameOverFlag == 1) {
			break;
		}
		int temp = 0;
		for (int begin = 1; begin < ROW; begin++)
		{
			if (map[i][begin] != 0)
			{
				if (map[i][temp] == 0)
				{
					map[i][temp] = map[i][begin];
					map[i][begin] = 0;;
				}
				else if (map[i][temp] == map[i][begin])
				{
					map[i][temp] += map[i][begin];
					//计分
					ScoreCalculation(map[i][temp]);
					map[i][begin] = 0;
					temp++;
				}
				else
				{
					map[i][temp + 1] = map[i][begin];
					if (temp + 1 != begin)
					{
						map[i][begin] = 0;
					}
					temp++;
				}
				if (isChanged()) {
					movedflag = 1;
				}
			}
		}
	}
}
//向右移动
void moveRight()
{
	for (int i = 0; i < ROW; i++)
	{
		if (gameInfo.gameOverFlag == 1) {
			break;
		}
		int temp = COL - 1;
		for (int begin = COL - 2; begin >= 0; begin--)
		{
			if (map[i][begin] != 0)
			{
				if (map[i][temp] == 0)
				{
					map[i][temp] = map[i][begin];
					map[i][begin] = 0;
				}
				else if (map[i][temp] == map[i][begin])
				{
					map[i][temp] += map[i][begin];
					ScoreCalculation(map[i][temp]);
					map[i][begin] = 0;
					temp--;
				}
				else
				{
					map[i][temp - 1] = map[i][begin];
					if (temp - 1 != begin)
					{
						map[i][begin] = 0;
					}
					temp--;
				}
				if (isChanged()) {
					movedflag = 1;
				}
			}
		}
	}
}
//移动格子
bool move(direction dir)
{
	copyData();
	//获取键盘按键 72 80 75 77
	switch (dir)
	{
	case UP:
		moveUp();
		break;
	case DOWN:
		moveDown();
		break;
	case LEFT:
		moveLeft();
		break;
	case RIGHT:
		moveRight();
		break;
	}
	
	if (movedflag == 1)
	{
		mapFillNumber();
		movedflag = 0;
	}

	gameOverCheck();
	
	return 1;
}

//游戏结束检测，为重启按钮做准备
void gameOverCheck() {
	if (gameInfo.emptyBlock != 0)
		return;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if ((j + 1 < 4 && map[i][j] == map[i][j + 1]) || (i + 1 < 4 && map[i][j] == map[i + 1][j]))
				return;
		}
	}
	gameInfo.gameOverFlag = 1;
}

//游戏数据写入文件的函数
void gameSave()
{
	//数据写入
	FILE* fp;
	
	errno_t err=fopen_s(&fp, "recordfile.dat", "w");
	if (fp == NULL||err!=0)
		return;
	fprintf(fp, "top_score:%d\ncurrent_score:%d\nmaxNum:%d\ncurrent_maxNum:%d",
		gameInfo.maxScore, gameInfo.currentScore, gameInfo.maxMergeNum, gameInfo.currentMaxMergeNum);
	fprintf(fp, "\n");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			fprintf(fp, "%4d ", map[i][j]);
		fprintf(fp, "\n");
	}
	fclose(fp);
}
