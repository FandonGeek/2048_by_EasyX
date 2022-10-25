#include"Game.h"
//存储数据的数组
int map[ROW][COL];
int flag = 0; //是否生成一个数字
struct gameInfo
{
	int MaxScore = 0;//存储最高分数
	int CurrentScore = 0;//存储当前分数
	int MaxMergeNum = 0;//最大合成数字
}gameInfo;

//随机产生2or4 2的概率更高
//游戏
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
//游戏
void mapFillNumber()
{
	//随机产生两个下标
	while (true)
	{
		//多次产生下标的时候，可能会重复 0 1 0 1 虽然概率比较小但还是有可能
		int r = rand() % ROW;	//0 1 2 3
		int c = rand() % COL;	//0 1 2 3
		//避免出现问题 首先判断原来位置是不是等于 0 如果等于 0 才放入数据
		if (map[r][c] == 0)
		{
			map[r][c] = createNumber();
			return;
		}
	}
}


//初始化
//游戏
void init()
{
	//设置随机数种子
	srand(time(NULL));

	//随机产生一个数，并且放到数组里面去 map[?][?] = createNumber();
	for (int i = 0; i < 2; i++)
	{
		mapFillNumber();
	}
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
				flag = 1;
			}
		}
	}
}
//向下移动
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
				flag = 1;
			}
		}
	}
}
//向左移动
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
				flag = 1;
			}
		}
	}
}
//向右移动
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
				flag = 1;
			}
		}
	}
}
//移动格子
void move()
{
	//获取键盘按键 72 80 75 77
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
	if (flag == 1)
	{
		mapFillNumber();
		flag = 0;
	}
}
