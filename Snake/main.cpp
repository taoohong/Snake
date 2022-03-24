#include "main.h"
#include "game.h"


int main(void)
{
	Game* game = new Game();
	while (game->is_running())
	{
		game->refresh(); 
		game->input_listener();
	}
	delete game;
	return 0;
}

//#include <graphics.h>  
//#include <conio.h>
//#include <stdio.h>
//#define BLOCK_SIZE 20 
//#define HEIGHT 30 
//#define WIDTH 40 
//
//int Blocks[HEIGHT][WIDTH] = { 0 }; 
//char moveDirection;  
//int food_i, food_j; 
//int isFailure = 0;
//
//void moveSnake() 
//{
//	int i, j;
//	for (i = 0; i < HEIGHT; i++) 
//		for (j = 0; j < WIDTH; j++) 
//			if (Blocks[i][j] > 0)
//				Blocks[i][j]++; 
//	int oldTail_i, oldTail_j, oldHead_i, oldHead_j; 
//	int max = 0; 
//	for (i = 0; i < HEIGHT; i++) 
//	{
//		for (j = 0; j < WIDTH; j++)
//		{
//			if (max < Blocks[i][j]) 
//			{
//				max = Blocks[i][j];
//				oldTail_i = i;
//				oldTail_j = j; 
//			}
//			if (Blocks[i][j] == 2) 
//			{
//				oldHead_i = i;
//				oldHead_j = j; 
//			}
//		}
//	}
//	int newHead_i = oldHead_i; 
//	int newHead_j = oldHead_j;
//
//	
//	if (moveDirection == 'w') 
//		newHead_i = oldHead_i - 1;
//	else if (moveDirection == 's') 
//		newHead_i = oldHead_i + 1;
//	else if (moveDirection == 'a') 
//		newHead_j = oldHead_j - 1;
//	else if (moveDirection == 'd') 
//		newHead_j = oldHead_j + 1;
//
//	if (newHead_i >= HEIGHT || newHead_i < 0 || newHead_j >= WIDTH || newHead_j < 0
//		|| Blocks[newHead_i][newHead_j]>0)
//	{
//		isFailure = 1; 
//		return; 
//	}
//
//	Blocks[newHead_i][newHead_j] = 1; 
//	if (newHead_i == food_i && newHead_j == food_j) 
//	{
//		food_i = rand() % (HEIGHT - 5) + 2; 
//		food_j = rand() % (WIDTH - 5) + 2; 
//	}
//	else 
//		Blocks[oldTail_i][oldTail_j] = 0; 
//}
//
//void startup()  
//{
//	int i;
//	Blocks[HEIGHT / 2][WIDTH / 2] = 1;
//	for (i = 1; i <= 4; i++) 
//		Blocks[HEIGHT / 2][WIDTH / 2 - i] = i + 1;
//	moveDirection = 'd';	 
//	food_i = rand() % (HEIGHT - 5) + 2; 
//	food_j = rand() % (WIDTH - 5) + 2;
//	initgraph(WIDTH * BLOCK_SIZE, HEIGHT * BLOCK_SIZE); 
//	setlinecolor(RGB(200, 200, 200)); 
//	BeginBatchDraw(); 
//}
//
//void show() 
//{
//	cleardevice(); 
//	int i, j;
//	for (i = 0; i < HEIGHT; i++) 
//	{
//		for (j = 0; j < WIDTH; j++)
//		{
//			if (Blocks[i][j] > 0) 
//				setfillcolor(HSVtoRGB(Blocks[i][j] * 10, 0.9, 1));
//			else
//				setfillcolor(RGB(150, 150, 150)); 
//			
//			fillrectangle(j * BLOCK_SIZE, i * BLOCK_SIZE,
//				(j + 1) * BLOCK_SIZE, (i + 1) * BLOCK_SIZE);
//		}
//	}
//	setfillcolor(RGB(0, 255, 0)); 
//	
//	fillrectangle(food_j * BLOCK_SIZE, food_i * BLOCK_SIZE,
//		(food_j + 1) * BLOCK_SIZE, (food_i + 1) * BLOCK_SIZE);
//	if (isFailure) 
//	{
//		setbkmode(TRANSPARENT); 
//		settextcolor(RGB(255, 0, 0));
//		settextstyle(80, 0, _T("LOL")); 
//		outtextxy(240, 220, _T("LOL")); 
//	}
//	FlushBatchDraw();
//}
//
//void updateWithoutInput() 
//{
//	if (isFailure) 
//		return;
//	static int waitIndex = 1;
//	waitIndex++; 
//	if (waitIndex == 10) 
//	{
//		moveSnake(); 
//		waitIndex = 1; 
//	}
//}
//
//void updateWithInput()  
//{
//	if (_kbhit() && isFailure == 0)  
//	{
//		char input = _getch(); 
//		if (input == 'a' || input == 's' || input == 'd' || input == 'w') 
//		{
//			moveDirection = input;
//			moveSnake(); 
//		}
//	}
//}
//
//int main()
//{
//	startup(); 
//	while (1)  
//	{
//		show(); 
//		updateWithoutInput(); 
//		updateWithInput();   
//	}
//	return 0;
//}