// Sheng Jiang
#include "mylib.h"
#include "objects.h"
#include <stdlib.h> 

// This function initializes the settings used in the game
void init_settings(Settings *settings){
	settings->difficulty = 10;
	settings->speed = 20;
	settings->score = 0;
}// end init_settings

// This function initializes the snake
void init_snake(Snake *snake){

	snake->x[0] = 4;
	snake->y[0] = 3;
	snake->tail = 0;
	snake->head = 0;
	snake->len = 1;
	snake->dx = 1;
	snake->dy = 0;
	snake->lastx = 4;
	snake->lasty = 2;
	snake->finished = 0;

}// end init_snake

// This function initializes the food
void init_food(Food *food){
	food->x = 2;
	food->y = 10;
}// end init_food

// This function creates a new random position for food (ensures that food is not created on snake)
void new_food(Food *food, Snake snake){
	int taken[MAXARR];
	int i = snake.tail;
	int num = MAXARR;
	while (i != snake.head){
		taken[snake.x[i]+snake.y[i]*(MAX_X+1)] = 1;
		i++;
		num--;
		if (i >= MAXARR){
			i = 0;
		}
	}
	i = 0;
	int count = 0;
	int newFood = rand() % num;
	while(count != newFood){
		if (taken[i] != 1){
			count++;
		}
		if (i >= MAXARR){
			i = 0;
			break;
		}
		i++;
	}
	int x = i;
	int y = 0;
	while (x > MAX_X){
		x += 0-MAX_X-1;
		y+=1;
	}
	food->x = x;
	food->y = y;
	
}// end new_food

// This function draws the food block
void draw_food(Food food, u16 color){
	drawBlock(food.x, food.y, color);
}// end draw_food

// This function draws the new head of the snake and clears the previous tail (the only things that change after each iteration)
void draw_snake(Snake snake, u16 fg, u16 bg){
	drawBlock(snake.lastx, snake.lasty, bg);
	drawBlock(snake.x[snake.head],snake.y[snake.head],fg);
}// end draw_snake

// This function iterates the snake (moves head and tail and checks for collision and food)
int iter_snake(Snake *snake, Food *food){
	int nextx = snake->x[snake->head]+snake->dx;
	int nexty = snake->y[snake->head]+snake->dy;
	int i = snake->tail;
	int ret = 0;
	while (i != snake->head){
		if(snake->x[i]==nextx && snake->y[i]==nexty){
			snake->finished = 1;
		}
		i++;
		if (i >= MAXARR){
			i = 0;
		}
	}
	if (nextx == food->x && nexty == food->y){
		snake->len++;
		snake->tail--;
		food->x=-1;
		ret = 1;
	}
	snake->lastx = snake->x[snake->tail];
	snake->lasty = snake->y[snake->tail];
	if (nextx > MAX_X){
		nextx = MAX_X;
		snake->finished = 1;
	}
	if (nextx < 0){
		nextx = 0;
		snake->finished = 1;
	}
	if (nexty > MAX_Y){
		nexty = MAX_Y;
		snake->finished = 1;
	}
	if (nexty < 0){
		nexty = 0;
		snake->finished = 1;
	}
	snake->tail ++;
	snake->head ++;
	
	if (snake->tail >= MAXARR){
		snake->tail = 0;
	}
	if (snake->head >= MAXARR){
		snake->head = 0;
	}
	snake->x[snake->head] = nextx;
	snake->y[snake->head] = nexty;
	return ret;
}// end iter_snake

// This function draws the blocks in the game (snake and food)
void drawBlock(int x, int y, u16 color){
	drawRect(y*BLOCKSIZE+BLOCKSIZE, x*BLOCKSIZE+BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, color);

//void drawRect(int r, int c, int height, int width, u16 color){
}// end drawBlock
