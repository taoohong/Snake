#ifndef GAME_HEAD_FILE
#define GAME_HEAD_FILE

#include "snake.h"

#define WIDTH  50
#define HEIGHT  30
#define BLOCK_SIZE 20

enum class Stuff_Mark 
{
	m_wall,
	m_ground,
	m_food,
	m_snake
};

enum class State
{
	gaming_state,
	restart_state,
	fail_state
};

typedef struct _stuff {
	int pos_x;
	int pos_y;
	Stuff_Mark mark;
}Stuff;

typedef enum _option
{
	move_up = 'w',
	move_right = 'd',
	move_down = 's',
	move_left = 'a',

	esc = 27,
	no_option = 0
}Option;

class Game 
{
private:
	int score;
	Stuff map[HEIGHT][WIDTH];
	Stuff* food;
	Snake* snake;
	State state;
	int input = no_option;
	int last_input = no_option;

	void init_map();
	void init_snake();
	void display_mark(Stuff* stuff);
	void snake_move(Direction direction);
	void move_handler(int* input, int* last_input);
	void init_food();

public:
	Game();
	bool is_running();
	void refresh();
	void input_listener();

	~Game();
};

#endif // !GAME_HEAD_FILE 

