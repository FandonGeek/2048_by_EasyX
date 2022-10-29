#include"Game.h"
#include <stdio.h>
#include<string.h>

//�洢���ݵ�����
int map[ROW][COL];//���и���
int movedflag = 0; //�Ƿ�����һ������
GameInfo gameInfo;//��Ϸ������ֵ��

//��ȡ�ļ�����
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
			// ��ȡ���ݳ������������Ч
			if ((readInCount != 1) || (map[i][j] < 0) || (4096 <= map[i][j])) {
				fclose(recordReader);
				init();
				return;
			}
			if (map[i][j] != 0)
				gameInfo.emptyBlock--;
		}
	}
	fclose(recordReader);
}

//�������2or4 2�ĸ��ʸ���
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

//������հ״����һ����
//20221028��д
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

//��ʼ��������Ϸ�����ĺ���
void init()
{
	//�����0��ʼ��
	memset(map, 0, sizeof(int) * 16);
	//�������������
	srand((unsigned int)time(NULL));

	//��Ϸ����
	gameInfo.gameOverFlag = 0;

	//����ֵ��0
	gameInfo.currentMaxMergeNum = 2;
	gameInfo.currentScore = 0;
	gameInfo.emptyBlock = 16;

	//�������һ���������ҷŵ���������ȥ map[?][?] = createNumber();
	for (int i = 0; i < 2; i++)
	{
		mapFillNumber();
	}
	
}

//��������ߺϳ����Ϳ��������������
void ScoreCalculation(int MergeNum) {
	//20221028����
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

//�����ƶ�
void moveUp()
{
	/*
	�����ƶ�:����ÿ��
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
					//�Ʒ�
					ScoreCalculation(map[temp][i]);
					map[begin][i] = 0;
					temp++;
				}
				else
				{
					map[temp + 1][i] = map[begin][i];
					if (temp + 1 != begin)//���temp+1��begn����ͬһ��λ��,����begin���ڵ�λ�õ������ÿ�
					{
						map[begin][i] = 0;
					}
					temp++;
				}
				movedflag = 1;
			}
		}
	}
}
//�����ƶ�
void moveDown()
{
	for (int i = 0; i < COL; i++)
	{
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
					//�Ʒ�
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
				movedflag = 1;
			}
		}
	}
}
//�����ƶ�
void moveLeft()
{
	for (int i = 0; i < COL; i++)
	{
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
					//�Ʒ�
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
				movedflag = 1;
			}
		}
	}
}
//�����ƶ�
void moveRight()
{
	for (int i = 0; i < ROW; i++)
	{
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
				movedflag = 1;
			}
		}
	}
}
//�ƶ�����
bool move()
{
	//��ȡ���̰��� 72 80 75 77
	int key = _getch();
	switch (key)
	{
	case 'W':
	case 'w':
	case 72:
		moveUp();
		break;
	case 'S':
	case 's':
	case 80:
		moveDown();
		break;
	case 'A':
	case 'a':
	case 75:
		moveLeft();
		break;
	case 'D':
	case 'd':
	case 77:
		moveRight();
		break;
	}
	
	if (movedflag == 1)
	{
		mapFillNumber();
		movedflag = 0;
	}
	
	return 1;
}

//��Ϸ������⣬Ϊ������ť��׼��
//��ʱľ��ʹ��
//20221026����
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

//��Ϸ����д���ļ��ĺ���
void gameSave()
{
	//����д��
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
