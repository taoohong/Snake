#include "snake.h"
#include <stdio.h>
#include <Windows.h>

Snake::Snake(int pos_x, int pos_y)
{
	init_pool();
	head = get_node();
	length = 1;
	speed = Speed::normal;
	head->dir = Direction::right;
	head->pos_x = pos_x;
	head->pos_y = pos_y;
	head->next_node = head;
	head->previous_node = head;
}

void Snake::init_pool()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		node_pool[i] = NULL;
	}
}

Snake_Body_Node* Snake::mknode()
{
	Snake_Body_Node* node = (Snake_Body_Node*)malloc(sizeof(Snake_Body_Node));
	if (node == NULL)
	{
		printf("out of memory");
		exit(1);
	}
	node->dir = Direction::right;
	node->pos_x = 0;
	node->pos_y = 0;
	node->next_node = NULL;
	node->previous_node = NULL;
	return node;
}

Snake_Body_Node* Snake::get_node()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (node_pool[i] != NULL)
		{
			Snake_Body_Node* ret =  node_pool[i];
			node_pool[i] = NULL;
			return ret;
		}
	}
	return mknode();
}

void Snake::free_node(Snake_Body_Node* node)
{
	node->pos_x = 0;
	node->pos_y = 0;
	node->previous_node = NULL;
	node->next_node = NULL;
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (node_pool[i] == NULL)
		{
			node_pool[i] = node;
			return;
		}
	}
	free(node);
	node = NULL;
	return;
}

void Snake::add_head_node( int pos_x, int pos_y) 
{
	Snake_Body_Node *body = get_node();
	body->pos_x = pos_x;
	body->pos_y = pos_y;
	body->dir = head->dir;
	body->previous_node = head->previous_node;
	head->previous_node->next_node = body;
	head->previous_node = body;
	body->next_node = head;
	head = body;
	length++;
}

void Snake::remove_tail_node()
{
	Snake_Body_Node *tail = head->previous_node;
	head->previous_node = tail->previous_node;
	tail->previous_node->next_node = head;
	free_node(tail);
	length--;
}


void Snake::move(Direction dir, int pos_x, int pos_y) {
	Sleep(((int)Speed::fast - (int)speed + 1)*50);
	Snake_Body_Node* tail = head->previous_node;
	tail->pos_x = pos_x;
	tail->pos_y = pos_y;
	tail->dir = dir;
	head = tail;
}

void Snake::eat( Direction dir, int pos_x, int pos_y) {
	Sleep(((int)Speed::fast - (int)speed + 1) * 50);
	head->dir = dir;
	add_head_node(pos_x, pos_y);
}

int Snake::get_length()
{
	return this->length;
}

Snake_Body_Node* Snake::get_head()
{
	return head;
}

Snake_Body_Node* Snake::get_tail()
{
	return head->previous_node;
}

Snake::~Snake()
{
	while (length > 1) {
		remove_tail_node();
	}
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (node_pool[i] != NULL)
		{
			free(node_pool[i]);
			node_pool[i] = NULL;
		}
	}
	free(head);
	head = NULL;
}

void Snake::set_speed(Speed speed)
{
	this->speed = speed;
}
