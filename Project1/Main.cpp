#include<stdio.h>
#include<easyx.h>
#include"tools.h"
#include"Game.h"

#define INTERVAL  15	//格子间的间隔
#define GRID_SIZE 117   //格子的宽度和高度
//38 * 195
IMAGE bk;				//背景

//定义图片资源
IMAGE imgs[11];
//特殊处理空白图片
IMAGE zero;

extern int map[ROW][COL];
extern int flag;
extern struct gameInfo;

void loadResource();
void draw();

int main(void)
{
	//窗口
	initgraph(584, 734, EX_SHOWCONSOLE);

	init();
	loadResource();


	drawImg(0, 0, &bk);
	while (true)
	{
		draw();
		move();
		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				printf("%d", map[i][j]);
			}
			printf("\n");
		}
	}
	getchar();
	return 0;
}

//资源加载
//界面函数
void loadResource()
{
	loadimage(&bk, "./pieces/bk.png", 584, 734);
	loadimage(&zero, "./pieces/0.png", GRID_SIZE, GRID_SIZE);
	for (int i = 2, j = 0; i <= 2048; i *= 2, j++)
	{
		char imgPath[50] = { 0 };                           //字符串格式化
		sprintf_s(imgPath, "./pieces/%d.png", i);           //缓冲区(数组) 格式字符串
		for (int i = 0; i < 17; i++)					    //字符数组必须要用for循环做打印|不能用"%s"的方式打印
		{
			printf("%c", imgPath[i]);
		}
		putchar('\n');

		//注意: 图片要一个挨着一个输出
		loadimage(&imgs[j], imgPath, GRID_SIZE, GRID_SIZE); //多字节字符集
	}
}

//绘制
//界面函数
void draw()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
			//把每个格子左上角的坐标求出来
			int x = k * GRID_SIZE + (k + 1) * INTERVAL + 38 - 18;
			int y = i * GRID_SIZE + (i + 1) * INTERVAL + 195 - 17;
			switch (map[i][k]) {
			case 0:
				drawImg(x, y, &zero);
				break;
			case 2:
				drawImg(x, y, &imgs[0]);
				break;
			case 4:
				drawImg(x, y, &imgs[1]);
				break;
			case 8:
				drawImg(x, y, &imgs[2]);
				break;
			case 16:
				drawImg(x, y, &imgs[3]);
				break;
			case 32:
				drawImg(x, y, &imgs[4]);
				break;
			case 64:
				drawImg(x, y, &imgs[5]);
				break;
			case 128:
				drawImg(x, y, &imgs[6]);
				break;
			case 256:
				drawImg(x, y, &imgs[7]);
				break;
			case 512:
				drawImg(x, y, &imgs[8]);
				break;
			case 1024:
				drawImg(x, y, &imgs[9]);
				break;
			case 2048:
				drawImg(x, y, &imgs[10]);
				break;
			}
		}
		printf("\n");
	}
}


