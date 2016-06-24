

#include "stdafx.h"


#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <conio.h>
#include<Windows.h>

using namespace std;
bool GameOver;
const int width = 30, height = 30;
int x, y, fruitx, fruity, score;
int nTail, TailX[100], TailY[100];
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void setup()
{
	GameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;

	fruitx = rand() % width;
	fruity = rand() % height;
}


void draw()
{
	int i, j;
	system("cls");
	cout <<"Your Score is "<< score;
	cout << endl;
	for (i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;

	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruity && j == fruitx)
				cout << "F";
			
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (TailX[k] == j && TailY[k] == i)
					{
						cout << "o";
						print = true;

					}
				}
				if(!print)
				cout << " ";
			}

			 if (j == width - 1)
				cout << "#";

		}
		cout << endl;

	}

	for (i = 0; i<width+2; i++)
		cout << "#";

}

void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;

		case 'd':
			dir = RIGHT;
			break;

		case 'w':
			dir = UP;
			break;

		case 's':
			dir = DOWN;
			break;

		case 'x':
			GameOver = true;
			break;

		}
	}
}

void logic()
{
	int prevX2, prevY2, i;
	int prevX = TailX[0];
	int prevY = TailY[0];
	TailX[0] = x;
	TailY[0] = y;
	for (i = 1; i < nTail; i++)
	{
		prevX2 = TailX[i];
		prevY2 = TailY[i];
		TailX[i] = prevX;
		TailY[i] = prevY;
		prevX = prevX2;
		prevY = prevY2;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;

	case RIGHT:
		x++;
		break;

	case UP:
		y--;
		break;

	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x > width || x<0 || y>height || y < 0)
		GameOver = true;
	//for (i = 0; i <= nTail; i++)
	//{
		//if (TailX[i] == x && TailY[i] == y)
			//asGameOver = true;
	//}
	if (x == fruitx && y == fruity)
	{
		score += 10;
		fruitx = rand() % width;
		fruity = rand() % height;
		nTail++;

	}
}

int main()
{
	setup();
	while (!GameOver)
	{
		draw();
		input();
		logic();
		Sleep(65);
	}

	return 0;
}
