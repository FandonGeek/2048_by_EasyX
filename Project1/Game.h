#pragma once
#include<stdlib.h>
#include<time.h>	
#include<math.h>
#include<conio.h>
#define ROW 4
#define COL 4	

//extern int map[ROW][COL];
//extern int flag;

int createNumber();
void mapFillNumber();
void init();
void moveUp();
void moveDown();
void moveRight();
void moveLeft();
void move();