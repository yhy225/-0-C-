#include <stdio.h>
#include <easyx.h>
#include <conio.h>
#include <graphics.h>
//制作界面
//创建一个图形窗口 easyx.h库函数
#define SNAKE_NUM 500 //蛇的最大节数
enum DIR //表示蛇的方向
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

//蛇的结构
struct Snake
{
	int size;//蛇的节数
	int dir;//蛇的方向
	int speed;//蛇的移动速度
	POINT coor[SNAKE_NUM];//坐标
}snake;
//食物结构
struct Food
{
	int x;
	int y;
	int r;//食物大小
	bool flag;//食物是否被吃
	DWORD color;//食物的颜色

}food;
//数据的初始化
void GameInit()
{
	//init 初始化  graph 图形窗口 SHOWCONSOLE显示控制台
	initgraph(640, 480 /*,SHOWCONSOLE*/);
	//设置随机数种子
	srand(GetTickCount());
	//初始化蛇
	snake.size = 3;//蛇的初始有3节
	snake.speed = 10;//蛇的速度
	snake.dir = RIGHT;//蛇的方向
	for (int i = 0;i < snake.size; i++)
	{
		snake.coor[i].x = 40-10*i;
		snake.coor[i].y = 10;
	}
	//初始化食物 rand()随机产生一个整数
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand()%256, rand() % 256, rand() % 256);
	food.r = rand() % 10 + 5;
	food.flag = true;
}
void GameDraw()
{
	//双缓冲绘图
	BeginBatchDraw();
	//设置背景颜色
	setbkcolor(RGB(28, 115, 119));
	cleardevice();//清空绘图设备
	//绘制蛇
	setfillcolor(WHITE);
	for (int i = 0; i < snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	//绘制食物
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.r);
	}
	EndBatchDraw();
}
//蛇的移动
void snakeMove()
{
	//让身体跟着头移动
	for (int i = snake.size-1; i >0; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}
	//移动即坐标发生改变	
	switch (snake.dir)
	{
	case UP:
		snake.coor[0].y-=snake.speed;
		if (snake.coor[0].y+10 <=0)//超出上面的边界
		{
			snake.coor[0].y = 480;
		}
		break;
	case DOWN:
		snake.coor[0].y+= snake.speed;
		if (snake.coor[0].y - 10 >= 480)
		{
			snake.coor[0].y = 0;
		}
		break;
	case LEFT:
		snake.coor[0].x-= snake.speed;
		if (snake.coor[0].x + 10 <= 0)
		{
			snake.coor[0].x = 640;
		}
		break;
	case RIGHT:
		snake.coor[0].x+= snake.speed;
		if (snake.coor[0].x - 10 >= 640)
		{
			snake.coor[0].x = 0;
		}
		break;
	
	}	
}
//通过按键改变蛇的移动方向
void keyControl()
{
	//判断有没有按键
	if (_kbhit())//检测如果有按键就返回真
	{
		//72 80 75 77 上下左右键值
		switch (_getch())
		{
		case 'w':
		case 'W':
		case 72:
			//只改变方向就OK
			if (snake.dir != DOWN)
			{
				snake.dir = UP;
			}
			
			break;
		case 's':
		case 'S':
		case 80:
			//改变方向
			if (snake.dir != UP)
			{
				snake.dir = DOWN;
			}
			
			break;
		case 'a':
		case 'A':
		case 75:
			//改变方向
			if (snake.dir != RIGHT)
			{
				snake.dir = LEFT;
			}
			
			break;
		case 'd':
		case 'D':
		case 77:
			//改变方向
			if (snake.dir != LEFT)
			{
				snake.dir = RIGHT;
			}
			
			break;
		case ' '://游戏暂停逻辑
			while (1)
			{
				if (_getch() == ' ')
					return;
			}
			break;
		}
	}	
}
void EatFood()
{
	if (food.flag && snake.coor[0].x >= food.x-food.r && snake.coor[0].x <= food.x+food.r &&
		snake.coor[0].y >= food.y - food.r && snake.coor[0].y <= food.y + food.r)
	{
		food.flag = false;
		snake.size++;
	}
	//如果食物消失，则重新生成一个食物
	if (!food.flag)
	{
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.r = rand() % 10 + 5;
		food.flag = true;
	}
	/*在这里可以加一个分数机制*/
}

int main()
{
	GameInit();
	while (1)
	{
		GameDraw();
		snakeMove();
		keyControl();
		EatFood();
		Sleep(60);//控制移动速度
	}
	return 0;
}

