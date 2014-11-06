// Sheng Jiang
#ifndef OBJECTS_H
#define OBJECTS_H

// Grid and array macros (currently a 10x10pixel grid)
#define BLOCKSIZE 10
#define MAXARR 308 //(240-BLOCKSIZE*2)*(160-BLOCKSIZE*2)/BLOCKSIZE/BLOCKSIZE
#define MAX_X 21 //240/BLOCKSIZE-3
#define MAX_Y 13 //160/BLOCKSIZE-3
#define MAXVALUE 500
#define MINVALUE 100

// The settings structure. Contains difficulty, speed, and score of current game.
typedef struct settings{
	int difficulty;
	int speed;
	int score;
} Settings;

// The snake structure. Contains circular arrays of the coordinates of the snake, as well as the last location of the snake tail.
typedef struct snake{
	int x[MAXARR];	//from 0 to 11
	int y[MAXARR];	//from 0 to 7
	int tail;
	int head;
	int len;
	int dx;
	int dy;
	int lastx;
	int lasty;
	int finished;
} Snake;

// The food structure. Contains the coordinates of the food.
typedef struct food{
	int x;
	int y;
} Food;

//function prototypes
void init_settings(Settings *settings);
void init_snake(Snake *snake);
void init_food(Food *food);
void new_food(Food *food, Snake snake);
void draw_food(Food food, u16 color);
void draw_snake(Snake snake, u16 fg, u16 bg);
int iter_snake(Snake *snake, Food *food);
void drawBlock(int x, int y, u16 color);

#endif
