#include <stdio.h>
#include <easyx.h>
#include <conio.h>
#include <graphics.h>
//��������
//����һ��ͼ�δ��� easyx.h�⺯��
#define SNAKE_NUM 500 //�ߵ�������
enum DIR //��ʾ�ߵķ���
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

//�ߵĽṹ
struct Snake
{
	int size;//�ߵĽ���
	int dir;//�ߵķ���
	int speed;//�ߵ��ƶ��ٶ�
	POINT coor[SNAKE_NUM];//����
}snake;
//ʳ��ṹ
struct Food
{
	int x;
	int y;
	int r;//ʳ���С
	bool flag;//ʳ���Ƿ񱻳�
	DWORD color;//ʳ�����ɫ

}food;
//���ݵĳ�ʼ��
void GameInit()
{
	//init ��ʼ��  graph ͼ�δ��� SHOWCONSOLE��ʾ����̨
	initgraph(640, 480 /*,SHOWCONSOLE*/);
	//�������������
	srand(GetTickCount());
	//��ʼ����
	snake.size = 3;//�ߵĳ�ʼ��3��
	snake.speed = 10;//�ߵ��ٶ�
	snake.dir = RIGHT;//�ߵķ���
	for (int i = 0;i < snake.size; i++)
	{
		snake.coor[i].x = 40-10*i;
		snake.coor[i].y = 10;
	}
	//��ʼ��ʳ�� rand()�������һ������
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand()%256, rand() % 256, rand() % 256);
	food.r = rand() % 10 + 5;
	food.flag = true;
}
void GameDraw()
{
	//˫�����ͼ
	BeginBatchDraw();
	//���ñ�����ɫ
	setbkcolor(RGB(28, 115, 119));
	cleardevice();//��ջ�ͼ�豸
	//������
	setfillcolor(WHITE);
	for (int i = 0; i < snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	//����ʳ��
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.r);
	}
	EndBatchDraw();
}
//�ߵ��ƶ�
void snakeMove()
{
	//���������ͷ�ƶ�
	for (int i = snake.size-1; i >0; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}
	//�ƶ������귢���ı�	
	switch (snake.dir)
	{
	case UP:
		snake.coor[0].y-=snake.speed;
		if (snake.coor[0].y+10 <=0)//��������ı߽�
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
//ͨ�������ı��ߵ��ƶ�����
void keyControl()
{
	//�ж���û�а���
	if (_kbhit())//�������а����ͷ�����
	{
		//72 80 75 77 �������Ҽ�ֵ
		switch (_getch())
		{
		case 'w':
		case 'W':
		case 72:
			//ֻ�ı䷽���OK
			if (snake.dir != DOWN)
			{
				snake.dir = UP;
			}
			
			break;
		case 's':
		case 'S':
		case 80:
			//�ı䷽��
			if (snake.dir != UP)
			{
				snake.dir = DOWN;
			}
			
			break;
		case 'a':
		case 'A':
		case 75:
			//�ı䷽��
			if (snake.dir != RIGHT)
			{
				snake.dir = LEFT;
			}
			
			break;
		case 'd':
		case 'D':
		case 77:
			//�ı䷽��
			if (snake.dir != LEFT)
			{
				snake.dir = RIGHT;
			}
			
			break;
		case ' '://��Ϸ��ͣ�߼�
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
	//���ʳ����ʧ������������һ��ʳ��
	if (!food.flag)
	{
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.r = rand() % 10 + 5;
		food.flag = true;
	}
	/*��������Լ�һ����������*/
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
		Sleep(60);//�����ƶ��ٶ�
	}
	return 0;
}

