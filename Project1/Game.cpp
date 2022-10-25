#include"Game.h"
//�洢���ݵ�����
int map[ROW][COL];
int flag = 0; //�Ƿ�����һ������
struct gameInfo
{
	int MaxScore = 0;//�洢��߷���
	int CurrentScore = 0;//�洢��ǰ����
	int MaxMergeNum = 0;//���ϳ�����
}gameInfo;

//�������2or4 2�ĸ��ʸ���
//��Ϸ
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
//��Ϸ
void mapFillNumber()
{
	//������������±�
	while (true)
	{
		//��β����±��ʱ�򣬿��ܻ��ظ� 0 1 0 1 ��Ȼ���ʱȽ�С�������п���
		int r = rand() % ROW;	//0 1 2 3
		int c = rand() % COL;	//0 1 2 3
		//����������� �����ж�ԭ��λ���ǲ��ǵ��� 0 ������� 0 �ŷ�������
		if (map[r][c] == 0)
		{
			map[r][c] = createNumber();
			return;
		}
	}
}


//��ʼ��
//��Ϸ
void init()
{
	//�������������
	srand(time(NULL));

	//�������һ���������ҷŵ���������ȥ map[?][?] = createNumber();
	for (int i = 0; i < 2; i++)
	{
		mapFillNumber();
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
				flag = 1;
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
//�ƶ�����
void move()
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
	if (flag == 1)
	{
		mapFillNumber();
		flag = 0;
	}
}
