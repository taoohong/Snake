#include "game.h"
#include <stdio.h>
#include <random>
#include <graphics.h>
#include <conio.h>

Game::Game()
{
	score = 0;
	state = State::gaming_state;
	snake = new Snake(5, 5);
	init_map();
	init_food();
	init_snake();
	initgraph(WIDTH * BLOCK_SIZE, HEIGHT * BLOCK_SIZE);
	setlinecolor(RGB(200, 200, 200));
	BeginBatchDraw();
}

bool Game::is_running()
{
	return state != State::fail_state;
}

Game::~Game()
{
	delete snake;
	food = NULL;
}

void Game::refresh()
{
	cleardevice();
	int i, j;
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			display_mark(&map[i][j]);
		}
	}
	if (state == State::fail_state)
	{
		setbkmode(TRANSPARENT);
		settextcolor(RGB(255, 0, 0));
		settextstyle(80, 0, _T("LOL"));
		outtextxy((WIDTH-10)*BLOCK_SIZE/2, (HEIGHT-5)*BLOCK_SIZE/2, _T("FAIL"));
	}
	FlushBatchDraw();
}


void Game::init_snake()
{
	Snake_Body_Node *head = snake->get_head(), * next = head;
	while (next->next_node != head)
	{
		map[head->pos_x][head->pos_y].mark = Stuff_Mark::m_snake;
		next = next->next_node;
	}
	map[head->pos_x][head->pos_y].mark = Stuff_Mark::m_snake;
}

void Game::init_food()
{
	int pos_x = 0;
	int pos_y = 0;
	while (!pos_x) pos_x = rand() % HEIGHT;
	while (!pos_y) pos_y = rand() % WIDTH;
	map[pos_x][pos_y].mark = Stuff_Mark::m_food;
	food = &map[pos_x][pos_y];
}

void Game::input_listener()
{
	if (_kbhit())
	{
		input = _getch();
	}
	else input = no_option;
	switch (input)
	{
	case move_up:
	case move_right:
	case move_down:
	case move_left:
		move_handler(&input, &last_input);
		break;
	case esc:
		state = State::fail_state;
		closegraph();
		break;
	case no_option:
	default:
		snake_move(snake->get_head()->dir);
		break;
	}
}

void Game::snake_move(Direction dir) 
{
	int pos_x = snake->get_head()->pos_x;
	int pos_y = snake->get_head()->pos_y;
	pos_y = dir == Direction::left ? pos_y - 1 : dir == Direction::right ? pos_y + 1 : pos_y;
	pos_x = dir == Direction::up ? pos_x - 1 : dir == Direction::down ? pos_x + 1 : pos_x;
	if (pos_y < 0 || pos_y >= WIDTH || pos_x < 0 || pos_x >= HEIGHT)
	{
		printf("[error]: pos_x, pos_y wrong!\n");
		exit(1);
	}
	switch (map[pos_x][pos_y].mark)
	{
	case Stuff_Mark::m_ground:
	{
		map[pos_x][pos_y].mark = Stuff_Mark::m_snake;
		Snake_Body_Node* tail = snake->get_head()->previous_node;
		map[tail->pos_x][tail->pos_y].mark = Stuff_Mark::m_ground;
		snake->move(dir, pos_x, pos_y);
		break;
	}
	case Stuff_Mark::m_food:
		map[pos_x][pos_y].mark = Stuff_Mark::m_snake;
		snake->eat(dir, pos_x, pos_y);
		init_food();
		score++;
		break;
	case Stuff_Mark::m_snake:
		printf("[info]: touch the snake itself!\n");
	case Stuff_Mark::m_wall:
		printf("[info]: touch the wall!\n");
		state = State::fail_state;
		break;
	default:
		break;
	}
}

void Game::display_mark(Stuff *stuff)
{
	switch (stuff->mark)
	{
	case Stuff_Mark::m_wall:
		setfillcolor(RGB(0, 0, 0));
		break;
	case Stuff_Mark::m_ground:
		setfillcolor(RGB(150, 150, 150));
		break;
	case Stuff_Mark::m_food:
		setfillcolor(RGB(0, 200, 0));
		break;
	case Stuff_Mark::m_snake:
		setfillcolor(HSVtoRGB(snake->get_length() * 10, 0.9, 1));
		break;
	default:
		break;
	}
	fillrectangle(stuff->pos_y * BLOCK_SIZE, stuff->pos_x * BLOCK_SIZE,
		(stuff->pos_y + 1) * BLOCK_SIZE, (stuff->pos_x + 1) * BLOCK_SIZE);
}

void Game::init_map()
{
	for (int i = 0; i < HEIGHT; i++) 
	{
		for (int j = 0; j < WIDTH; j++)
		{
			map[i][j].pos_x = i;
			map[i][j].pos_y = j;
			if (j == 0 || j == WIDTH-1 || i==0 || i==HEIGHT-1)
			{
				map[i][j].mark = Stuff_Mark::m_wall;
			}
			else map[i][j].mark = Stuff_Mark::m_ground;
		}
	 }
}

void Game::move_handler(int* input, int* last_input)
{
	if (*last_input + *input == move_down + move_up ||
		*last_input + *input == move_left + move_right)
	{
		snake_move(snake->get_head()->dir);
		return;
	}
	else if (*last_input == *input)
	{
		snake->set_speed(Speed::fast);
	}
	else
	{
		snake->set_speed(Speed::normal);
		*last_input = *input;
	}
	Direction dir = *input == move_up ? Direction::up : *input == move_down ?
		Direction::down : *input == move_left ? Direction::left :Direction:: right;
	snake_move(dir);
}

