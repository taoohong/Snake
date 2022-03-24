#ifndef _SNAKE_HEAD_FILE_
#define _SNAKE_HEAD_FILE_

#define POOL_SIZE 30

enum class Direction {
	up,
	right,
	down,
	left
};

enum class Speed {
	slow,
	normal,
	fast,
};

typedef struct _snake_body_node 
{
	int pos_x;
	int pos_y;
	Direction dir;
	struct _snake_body_node *previous_node;
	struct _snake_body_node *next_node;
}Snake_Body_Node;


class Snake
{
private:
	int length;
	Speed speed;
	Snake_Body_Node* head;
	Snake_Body_Node* node_pool[POOL_SIZE];

	void init_pool();
	Snake_Body_Node* mknode();
	Snake_Body_Node* get_node();
	void free_node(Snake_Body_Node* node);
	void add_head_node(int pos_x, int pos_y);
	void remove_tail_node();
	

public:
	Snake(int pox_x, int pos_y);
	~ Snake();

	void move(Direction dir, int pos_x, int pos_y);
	void eat(Direction dir, int pos_x, int pos_y);

	void set_speed(Speed speed);
	int get_length();
	Snake_Body_Node* get_head();
	Snake_Body_Node* get_tail();
};

#endif // !SNAKE_HEAD_FILE
