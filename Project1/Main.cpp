#include<stdio.h>
#include"tools.h"
#include"Game.h"
#include <conio.h>

#pragma comment(lib,"Winmm.lib")	//用于音乐播放的Windows API


#define INTERVAL  15	//格子间的间隔
#define GRID_SIZE 117   //格子的宽度和高度


//38 * 195
IMAGE bk;				//背景
IMAGE gameOver;         //游戏结束

//定义图片资源
IMAGE imgs[11];
//特殊处理空白图片
IMAGE zero;

extern int map[ROW][COL];
extern GameInfo gameInfo;

void loadImgs();
void loadResource();

void drawBackgroud();
void printGame();
void draw();
void drawGameInfo();
void drawBlocks();

//游戏窗口
int main(void)
{
	//窗口
	initgraph(584, 734, EX_SHOWCONSOLE);

	 

	loadResource();
	gameSave();

	BeginBatchDraw();//批量画图，无闪烁
	draw();
	EndBatchDraw();

	//音乐播放
	mciSendString(_T("open .\\pieces\\bk.mp3"), NULL, 0, NULL);
	mciSendString(_T("play .\\pieces\\bk.mp3 repeat"), NULL, 0, NULL);
	
	
	
	while (true)
	{
		//批量画图，无闪烁
		BeginBatchDraw();
		printGame();
		draw();
		EndBatchDraw();
		

		//凑合着用的游戏主界面运行方式
		int key;
		while (!_kbhit());
		key = _getch();
		switch (key)
		{
		case 'W':
		case 'w':
		case 72:
			move(UP);
			break;
		case 'S':
		case 's':
		case 80:
			move(DOWN);
			break;
		case 'A':
		case 'a':
		case 75:
			move(LEFT);
			break;
		case 'D':
		case 'd':
		case 77:
			move(RIGHT);
			break;
		case 'N':
		case 'n':
			init();
			break;
		default:
			break;
		}

		/* 还是有问题，体现在鼠标和键盘似乎不能在一个页面同时使用，
		 * 是要特殊的处理还是easyX的锅我暂且不知，先去补作业了
		ExMessage m;
		m = getmessage(EX_MOUSE);
		if (peekmessage(&m, EM_MOUSE)) {
			if (m.message == WM_LBUTTONDOWN) {
				if (m.x >= 427 && m.x <= 561 && m.y >= 107 && m.y <= 155) {
					init();
				}
			}
		}
		*/
		
		//游戏保存
		gameSave();
	}
	
	getchar();
	closegraph();
	return 0;
}


void loadImgs() {
	loadimage(&bk, "./pieces/bk.png", 584, 734);
	loadimage(&gameOver, "./pieces/gameOver.png", 300, 40);

	//0位贴图
	loadimage(&zero, "./pieces/0.png", GRID_SIZE, GRID_SIZE);

	//以下载入数字贴图
	for (int i = 2, j = 0; i <= 2048; i *= 2, j++)
	{
		char imgPath[50] = { 0 };                           //字符串格式化
		sprintf_s(imgPath, "./pieces/%d.png", i);           //缓冲区(数组) 格式字符串

		//文件加载测试函数
		for (int i = 0; i < 17; i++)					    //字符数组必须要用for循环做打印|不能用"%s"的方式打印
		{
			printf("%c", imgPath[i]);
		}
		putchar('\n');

		//注意: 图片要一个挨着一个输出
		loadimage(&imgs[j], imgPath, GRID_SIZE, GRID_SIZE); //多字节字符集
	}
}

//资源加载
//界面函数
void loadResource()
{
	//图像加载
	loadImgs();

	//游戏记录加载
	loadRecord();
}

//游戏控制台调试函数
void printGame()
{
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			printf("%4d", map[i][j]);
		}
		printf("\n");
	}
	printf("Cur:%d\nMax:%d\nMaxMergeNum:%d\nemptyBlock:%d\n", gameInfo.currentScore, gameInfo.maxScore, gameInfo.maxMergeNum, gameInfo.emptyBlock);
} 

//画图更新层
void draw() {
	drawGameInfo();
	drawBlocks();
	if (gameInfo.gameOverFlag == 1) {
		drawImg(150,350,&gameOver);
	}
}

//背景和分数
void drawGameInfo() {
	drawImg(0, 0, &bk);

	setbkmode(TRANSPARENT);
	settextcolor(RGB(241, 231, 214));
	settextstyle(20, 0,"黑体");
	char s1[10],s2[10];
	sprintf_s(s1, "%8d", gameInfo.currentScore);
	outtextxy(373, 50, s1);
	sprintf_s(s2, "%8d", gameInfo.maxScore);
	outtextxy(473, 50, s2);

	//配合全键盘操作所作的声明
	settextcolor(RGB(205, 133, 63));
	settextstyle(17,0, "黑体");
	char s3[0xff];
	sprintf_s(s3, "本页面使用键盘操作");
	outtextxy(20, 100, s3);
	sprintf_s(s3, "按方向键或W、S、A、D移动方块");
	outtextxy(20, 125, s3);
	sprintf_s(s3, "按N重新开始游戏");
	outtextxy(20, 150, s3);
}

//绘制数字块
void drawBlocks()
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


