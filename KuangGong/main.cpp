#include <graphics.h>
#include <stdio.h>
#include <string>
#include <ctime>
#include <conio.h>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 480
void FoodLocetion();

/*

			Tab��	�Զ�����ɱ
			�ո��	ײǽ��ɱ
*/
bool Open_EalFood_Take = 0;			//ok




int Score = 0;
/*����ö��*/
enum Face
{
	Up = 72,
	Down = 80,
	Left = 75,
	Right = 77
};
/*�߽ṹ��*/
struct Snake
{
	int x, y;
};
/*ʳ��ṹ��*/
struct Food
{
	int x, y;
	bool exist;
};
/*�ߵķ���*/
Face face;
/*�ߵ�ǰ�Ľ���*/
int n;
/*ʵ����*/
struct Snake snake[100];
/*ʳ��*/
Food food;
/*��Ϸ��ʼ��*/
void GameInit()
{
	/*�����ʼ��*/
	snake[0].x = 0;
	snake[0].y = 0;
	n = 3;
	/*���÷���*/
	face = Right;
	/*ʳ��λ��*/
	FoodLocetion();
}
/*����*/
void DrawSnake()
{
	cleardevice();
	for (int i = 0; i < n; i++)
	{
		fillrectangle(snake[i].x, snake[i].y, snake[i].x + 15, snake[i].y + 15);
	}
}
/*��ҿ���-�����Լ�*/
void switch_Open_EalFood_Take()
{
	if (Open_EalFood_Take)
	{
		Open_EalFood_Take = 0;
	}
	else
	{
		Open_EalFood_Take = 1;
	}
}
/*���񰴼������÷���*/
void KeyDown_SetFace()
{

	int Key = _getch();
	switch (Key)
	{
	case 9:
		/*��ҿ���-�����Լ�*/
		switch_Open_EalFood_Take();
		break;
	case Up:
		if (face != Down)
		{
			face = Up;
		}
		break;
	case Down:
		if (face != Up)
		{
			face = Down;
		}
		break;
	case Left:
		if (face != Right)
		{
			face = Left;
		}
		break;
	case Right:
		if (face != Left)
		{
			face = Right;
		}
		break;
	default:
		break;
	}
}
/*���ƶ�*/
void SnackMove()
{
	for (int i = n; i > 0; i--)
	{
		snake[i].x = snake[i - 1].x;
		snake[i].y = snake[i - 1].y;
	}
	switch (face)
	{
	case Up:
		snake[0].y -= 15;
		break;
	case Down:
		snake[0].y += 15;
		break;
	case Left:
		snake[0].x -= 15;
		break;
	case Right:
		snake[0].x += 15;
		break;
	default:
		break;
	}
}
/*ʳ��λ��*/
void FoodLocetion()
{
	srand(unsigned int(time(NULL)));
	food.x = rand() % 800 + 1;
	food.y = rand() % 480 + 1;
	food.exist = true;
}
/*��ʳ��*/
void DrawFood()
{
	fillcircle(food.x,food.y,10);
}
/*ʳ�ﱻ�Ե�*/
void is_Food()
{
	if (!food.exist)
	{
		FoodLocetion();
	}
}
/*�Ƿ�Ե�ʳ��*/
void is_Eatshit()
{
	if (snake[0].x + 15 >= food.x && snake[0].x <= food.x + 10)
	{
		if (snake[0].y + 15 >= food.y && snake[0].y <= food.y + 10)
		{
			if (Open_EalFood_Take)
			{
				closegraph();
				MessageBox(NULL,"��o(*������*)o","������",NULL);
			}
			else
			{
				Score++;
				food.exist = false;
				n++;
			}
		}
	}
	//if(snake[0].x + 15)
}
/*��ӡ����*/
void outScore()
{
	TCHAR bus[20] = TEXT("");
	wsprintf(bus, _T("Number: %d"), Score);
	outtextxy(0, 0, bus);
}
int main()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	GameInit();
	while (1)
	{
		while (!_kbhit())
		{
			/*���ƶ�*/
			SnackMove();
			/*����*/
			DrawSnake();
			/*��ʳ��*/
			DrawFood();
			/*�Ƿ�Ե�ʳ��*/
			is_Eatshit();
			/*ʳ��������Ե��ػ�*/
			is_Food();
			/*����Զ�ת��char��������ӡ����*/
			outScore();
			Sleep(100);
		}
		KeyDown_SetFace();
	}
	getchar();
	return 0;
}