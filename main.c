// Sheng Jiang
#include "mylib.h"
#include "objects.h"
#include "text.h"
#include<stdio.h>

// function prototype
void intro(Settings *sett);

// main function
int main(void){
	// set GBA parameters
	REG_DISPCNT = MODE3 | BG2_ENABLE;
	
	// initialize settings
	Settings settings;
	init_settings(&settings);
	
	// intro sequence (start screen and options)
	intro(&settings);
	
	// draw bg
	drawRect(0,0,160,240,BORDER);
	drawRect(BLOCKSIZE,BLOCKSIZE,160-BLOCKSIZE-BLOCKSIZE,240-BLOCKSIZE-BLOCKSIZE,GRASS);
	
	// initialize snake and food	
	Snake snake;
	Food food;
	init_snake(&snake);
	init_food(&food);
	
	// in-game variables
	int loop = 1;
	int pressed = 0;
	char buff[8];
	int value = MAXVALUE;
	sprintf (buff, "%8d", settings.score);
	drawString(2, 80, buff, APPLE);
	
	// main game loop
	while(loop){
		// prevents multiple button presses leading to the snake moving wrongly
		pressed = 0;
		// draws snake and food, and records movement
		for (int i = 0; i < settings.speed; i++){
			wait_for_vblank();
			draw_snake(snake, SNAKE, GRASS);
			draw_food(food, APPLE);
			if (pressed == 0){
				if (PRESSED(BUTTON_UP)){
					if(snake.dx != 0){
						snake.dx = 0;
						snake.dy = -1;
						pressed = 1;
					}
				}
				else if (PRESSED(BUTTON_DOWN)){
					if(snake.dx != 0){
						snake.dx = 0;
						snake.dy = 1;
						pressed = 1;
					}
				}
				else if (PRESSED(BUTTON_LEFT)){
					if(snake.dy != 0){
						snake.dx = -1;
						snake.dy = 0;
						pressed = 1;
					}
				}
				else if (PRESSED(BUTTON_RIGHT)){
					if(snake.dy != 0){
						snake.dx = 1;
						snake.dy = 0;
						pressed = 1;
					}
				}
			}
		}
		// reduce the value of the food over time
		if (value > MINVALUE){
			value += -1;
		}		
		// increase score if food is eaten
		if (iter_snake(&snake, &food) == 1){
			settings.score += value;
			value = MAXVALUE;
			sprintf (buff, "%8d", settings.score);
			drawRect(0, 80, 10, 60, BORDER);
			drawString(2, 80, buff, APPLE);
		}
		// if food eaten, create new food
		if (food.x < 0){
			new_food(&food, snake);
		}
		
		// ending
		if (snake.finished == 1 || snake.len > settings.difficulty){
			drawRect(60, 10, 30, 220, BORDER);
			if (snake.finished == 1){
				drawRect(0,0,BLOCKSIZE,240,RED);
				drawRect(0,0,160,BLOCKSIZE,RED);
				drawRect(160-BLOCKSIZE,0,BLOCKSIZE,240,RED);
				drawRect(0,240-BLOCKSIZE,160,BLOCKSIZE,RED);
				drawString(62,90,"You lost!",APPLE);
			}
			if (snake.len > settings.difficulty){
				drawRect(0,0,BLOCKSIZE,240,BLUE);
				drawRect(0,0,160,BLOCKSIZE,BLUE);
				drawRect(160-BLOCKSIZE,0,BLOCKSIZE,240,BLUE);
				drawRect(0,240-BLOCKSIZE,160,BLOCKSIZE,BLUE);
				drawString(62,90,"You won!",APPLE);
			}
			char score[40];
			sprintf (score, "Score: %d", settings.score);
			drawString(72, 90, score, APPLE);
			drawString(82, 90, "Try Again?", APPLE);
			// retry sequence
			while(1){
				wait_for_vblank();
				if (PRESSED(BUTTON_A)){
					// reset variables
					init_snake(&snake);
					init_food(&food);
					init_settings(&settings);
					intro(&settings);
					loop = 1;
					while(PRESSED(BUTTON_A)){;}
					drawRect(0,0,160,240,BORDER);
					drawRect(BLOCKSIZE,BLOCKSIZE,160-BLOCKSIZE-BLOCKSIZE,240-BLOCKSIZE-BLOCKSIZE,GRASS);
					break;
				}
				if (PRESSED(BUTTON_B)){loop=0;break;}
			}
			
		}
	}// end main game loop
}// end main

// intro sequence
void intro(Settings *sett){
	drawRect(0,0,160,240,BLACK);
	int option = 0;
	int cursor = 0;
	int loop = 1;
	char *startscreen1 = "Welcome to S N A K E";
	char *startscreen2 = "Press START";
	char *menu1 = "START";
	char *menu2 = "SPEED: ";
	int speed = 0;
	char option2[4] = "123";
	char *menu3 = "DIFFICULTY: ";
	int diff = 0;
	char option3[13] = "EASYMED HARD";
	drawRect(0,0,160,240,BLACK);
	while(loop){
		wait_for_vblank();
		// start screen sequence
		if (option == 0){
			drawString(20, 5, startscreen1, WHITE);
			drawString(40, 5, startscreen2, WHITE);
			if (PRESSED(BUTTON_START) || PRESSED(BUTTON_A)){
				while(PRESSED(BUTTON_START) || PRESSED(BUTTON_A)){;}
				option = 1;
				drawRect(20,5,60,140,BLACK);
			}
		}
		// option sequence
		else if (option == 1){
			drawString(20, 40, menu1, WHITE);
			drawString(40, 40, menu2, WHITE);
			drawChar(40, 120, option2[speed], RED);
			drawString(60, 40, menu3, WHITE);
			for (int i = 0; i < 4; i++){
				drawChar(60, 120+i*6, option3[i+diff*4], RED);
			}
			drawRect(20+cursor*20, 20, 10, 10, WHITE);
			if (PRESSED(BUTTON_UP)){
				cursor = (cursor+2) % 3;
				drawRect(20, 20, 140, 10, BLACK);
				drawRect(20+cursor*20, 20, 10, 10, WHITE);
				while(PRESSED(BUTTON_UP)){;}
			}
			else if (PRESSED(BUTTON_DOWN)){
				cursor = (cursor+1) % 3;
				drawRect(20, 20, 140, 10, BLACK);
				drawRect(20+cursor*20, 20, 10, 10, WHITE);
				while(PRESSED(BUTTON_DOWN)){;}
			}
			else if (PRESSED(BUTTON_LEFT)){
				if (cursor == 1){
					speed = (speed+2) % 3;
					drawRect(40, 120, 10, 10, BLACK);
					drawChar(40, 120, option2[speed], RED);
				}
				if (cursor == 2){
					diff = (diff+2) % 3;
					drawRect(60, 120, 10, 60, BLACK);
					for (int i = 0; i < 4; i++){
						drawChar(60, 120+i*6, option3[i+diff*4], RED);
					}
				}
				while(PRESSED(BUTTON_LEFT)){;}
			}
			else if (PRESSED(BUTTON_RIGHT)){
				if (cursor == 1){
					speed = (speed+1) % 3;
					drawRect(40, 120, 10, 10, BLACK);
					drawChar(40, 120, option2[speed], RED);
				}
				if (cursor == 2){
					diff = (diff+1) % 3;
					drawRect(60, 120, 10, 60, BLACK);
					for (int i = 0; i < 4; i++){
						drawChar(60, 120+i*6, option3[i+diff*4], RED);
					}
				}
				while (PRESSED(BUTTON_RIGHT)){;}
			}
			else if (PRESSED(BUTTON_A) || PRESSED(BUTTON_START)){
				if (cursor == 0){
					loop = 0;
					sett->speed = 50;
					switch (speed){
						case 0: sett->speed = 20; break;
						case 1: sett->speed = 10; break;
						case 2: sett->speed = 5; break;
					}
					sett->difficulty = 20;
					switch (diff){
						case 0: sett->difficulty = 20; break;
						case 1: sett->difficulty = 100; break;
						case 2: sett->difficulty = 384; break;
					}
				}
				if (cursor == 1){
				speed = (speed+1) % 3;
				drawRect(40, 120, 10, 10, BLACK);
				drawChar(40, 120, option2[speed], RED);
				}
				if (cursor == 2){
					diff = (diff+1) % 3;
					drawRect(60, 120, 10, 60, BLACK);
					for (int i = 0; i < 4; i++){
						drawChar(60, 120+i*6, option3[i+diff*4], RED);
					}
				}
				while (PRESSED(BUTTON_A) || PRESSED(BUTTON_START)){;}
			}
			else if (PRESSED(BUTTON_B)){
				option = 0;
				drawRect(20,5,60,140,BLACK);
			}
		}
	}// end intro loop

}// end intro
