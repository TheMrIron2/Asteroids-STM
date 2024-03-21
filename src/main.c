#include <stm32f031x6.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "../assets/assets.h"
#include "musical_notes.h"
#include "sound.h"
#include "display.h"
#include "player.h"
#include "board.h"

void initClock(void);
void initSysTick(void);
void SysTick_Handler(void);
void delay(volatile uint32_t dly);
void setupIO();
int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py);
void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber);
void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode);
void switch_symbol();
int check_win();

volatile uint32_t milliseconds;

// The player
struct player p;

// The cells
struct cell c1, c2, c3, c4, c5, c6, c7, c8, c9;

int main()
{
	// Starts clocks and system processes
	initClock();
	initSound();
	initSysTick();
	setupIO();
	init_player(&p);

	bool menu = 1;

	// Current cell number 1 -> 9, 0 if not in a cell
	int current_cell = 0;

	// Populates cells with information, yes I know it's a nightmare yes I hate myself.
	c1.centre = (struct position){(SCREEN_CENTRE_X - CELL_SIZE), (SCREEN_CENTRE_Y - CELL_SIZE)};
	c1.top_left = (struct position){(c1.centre.x - (CELL_SIZE / 2)), (c1.centre.y - (CELL_SIZE / 2))};
	c1.top_right = (struct position){(c1.centre.x + (CELL_SIZE / 2)), (c1.centre.y - (CELL_SIZE / 2))};
	c1.bottom_left = (struct position){(c1.centre.x - (CELL_SIZE / 2)), (c1.centre.y + (CELL_SIZE / 2))};
	c1.bottom_right = (struct position){(c1.centre.x + (CELL_SIZE / 2)), (c1.centre.y + (CELL_SIZE / 2))};
	c1.symbol = ' ';

	c2.centre = (struct position){SCREEN_CENTRE_X, (SCREEN_CENTRE_Y - CELL_SIZE)};
	c2.top_left = (struct position){(c2.centre.x - (CELL_SIZE / 2)), (c2.centre.y - (CELL_SIZE / 2))};
	c2.top_right = (struct position){(c2.centre.x + (CELL_SIZE / 2)), (c2.centre.y - (CELL_SIZE / 2))};
	c2.bottom_left = (struct position){(c2.centre.x - (CELL_SIZE / 2)), (c2.centre.y + (CELL_SIZE / 2))};
	c2.bottom_right = (struct position){(c2.centre.x + (CELL_SIZE / 2)), (c2.centre.y + (CELL_SIZE / 2))};
	c2.symbol = ' ';

	c3.centre = (struct position){(SCREEN_CENTRE_X + CELL_SIZE), (SCREEN_CENTRE_Y - CELL_SIZE)};
	c3.top_left = (struct position){(c3.centre.x - (CELL_SIZE / 2)), (c3.centre.y - (CELL_SIZE / 2))};
	c3.top_right = (struct position){(c3.centre.x + (CELL_SIZE / 2)), (c3.centre.y - (CELL_SIZE / 2))};
	c3.bottom_left = (struct position){(c3.centre.x - (CELL_SIZE / 2)), (c3.centre.y + (CELL_SIZE / 2))};
	c3.bottom_right = (struct position){(c3.centre.x + (CELL_SIZE / 2)), (c3.centre.y + (CELL_SIZE / 2))};
	c3.symbol = ' ';

	c4.centre = (struct position){(SCREEN_CENTRE_X - CELL_SIZE), SCREEN_CENTRE_Y};
	c4.top_left = (struct position){(c4.centre.x - (CELL_SIZE / 2)), (c4.centre.y - (CELL_SIZE / 2))};
	c4.top_right = (struct position){(c4.centre.x + (CELL_SIZE / 2)), (c4.centre.y - (CELL_SIZE / 2))};
	c4.bottom_left = (struct position){(c4.centre.x - (CELL_SIZE / 2)), (c4.centre.y + (CELL_SIZE / 2))};
	c4.bottom_right = (struct position){(c4.centre.x + (CELL_SIZE / 2)), (c4.centre.y + (CELL_SIZE / 2))};
	c4.symbol = ' ';

	c5.centre = (struct position){SCREEN_CENTRE_X, SCREEN_CENTRE_Y};
	c5.top_left = (struct position){(c5.centre.x - (CELL_SIZE / 2)), (c5.centre.y - (CELL_SIZE / 2))};
	c5.top_right = (struct position){(c5.centre.x + (CELL_SIZE / 2)), (c5.centre.y - (CELL_SIZE / 2))};
	c5.bottom_left = (struct position){(c5.centre.x - (CELL_SIZE / 2)), (c5.centre.y + (CELL_SIZE / 2))};
	c5.bottom_right = (struct position){(c5.centre.x + (CELL_SIZE / 2)), (c5.centre.y + (CELL_SIZE / 2))};
	c5.symbol = ' ';

	c6.centre = (struct position){(SCREEN_CENTRE_X + CELL_SIZE), SCREEN_CENTRE_Y};
	c6.top_left = (struct position){(c6.centre.x - (CELL_SIZE / 2)), (c6.centre.y - (CELL_SIZE / 2))};
	c6.top_right = (struct position){(c6.centre.x + (CELL_SIZE / 2)), (c6.centre.y - (CELL_SIZE / 2))};
	c6.bottom_left = (struct position){(c6.centre.x - (CELL_SIZE / 2)), (c6.centre.y + (CELL_SIZE / 2))};
	c6.bottom_right = (struct position){(c6.centre.x + (CELL_SIZE / 2)), (c6.centre.y + (CELL_SIZE / 2))};
	c6.symbol = ' ';

	c7.centre = (struct position){(SCREEN_CENTRE_X - CELL_SIZE), (SCREEN_CENTRE_Y + CELL_SIZE)};
	c7.top_left = (struct position){(c7.centre.x - (CELL_SIZE / 2)), (c7.centre.y - (CELL_SIZE / 2))};
	c7.top_right = (struct position){(c7.centre.x + (CELL_SIZE / 2)), (c7.centre.y - (CELL_SIZE / 2))};
	c7.bottom_left = (struct position){(c7.centre.x - (CELL_SIZE / 2)), (c7.centre.y + (CELL_SIZE / 2))};
	c7.bottom_right = (struct position){(c7.centre.x + (CELL_SIZE / 2)), (c7.centre.y + (CELL_SIZE / 2))};
	c7.symbol = ' ';

	c8.centre = (struct position){SCREEN_CENTRE_X, (SCREEN_CENTRE_Y + CELL_SIZE)};
	c8.top_left = (struct position){(c8.centre.x - (CELL_SIZE / 2)), (c8.centre.y - (CELL_SIZE / 2))};
	c8.top_right = (struct position){(c8.centre.x + (CELL_SIZE / 2)), (c8.centre.y - (CELL_SIZE / 2))};
	c8.bottom_left = (struct position){(c8.centre.x - (CELL_SIZE / 2)), (c8.centre.y + (CELL_SIZE / 2))};
	c8.bottom_right = (struct position){(c8.centre.x + (CELL_SIZE / 2)), (c8.centre.y + (CELL_SIZE / 2))};
	c8.symbol = ' ';

	c9.centre = (struct position){(SCREEN_CENTRE_X + CELL_SIZE), (SCREEN_CENTRE_Y + CELL_SIZE)};
	c9.top_left = (struct position){(c9.centre.x - (CELL_SIZE / 2)), (c9.centre.y - (CELL_SIZE / 2))};
	c9.top_right = (struct position){(c9.centre.x + (CELL_SIZE / 2)), (c9.centre.y - (CELL_SIZE / 2))};
	c9.bottom_left = (struct position){(c9.centre.x - (CELL_SIZE / 2)), (c9.centre.y + (CELL_SIZE / 2))};
	c9.bottom_right = (struct position){(c9.centre.x + (CELL_SIZE / 2)), (c9.centre.y + (CELL_SIZE / 2))};
	c9.symbol = ' ';

	// Title text
	printTextX2("X's + O's", 10, 10, RGBToWord(0xff,0xff,0), 0);
	printTextX2("But", 10, 30, RGBToWord(0xff,0xff,0), 0);
	printTextX2("Worse", 10, 50, RGBToWord(0xff,0xff,0), 0);
	printText("Press right", 30, 100, RGBToWord(0xff,0xff,0), 0);
	draw_player(&p);

	while(menu == 1)
	{

		if ((GPIOB->IDR & (1 << 4))==0) // right pressed
		{					
			menu = 0;
			fillRectangle(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		}
		delay(50);
	}

	int quit = 0;

	while(quit == 0)
	{

		current_cell = check_current_cell();
		
		if ((GPIOB->IDR & (1 << 4))==0) // right pressed
		{					
			rotate_player(&p, 6);
			playNote(4400);
			
		}
		if ((GPIOB->IDR & (1 << 5))==0) // left pressed
		{			
			rotate_player(&p, -6);
		}
		if ( (GPIOA->IDR & (1 << 11)) == 0) // down pressed
		{
			if (current_cell == 0) {
				// Do nothing
			}
			else if (current_cell == 1) {
				if (c1.symbol == ' ') {
					c1.symbol = p.symbol;
					switch_symbol();
				}
			}
			else if (current_cell == 2) {
				if (c2.symbol == ' ') {
					c2.symbol = p.symbol;
					switch_symbol();
				}
			}
			else if (current_cell == 3) {
				if (c3.symbol == ' ') {
					c3.symbol = p.symbol;
					switch_symbol();
				}
			}
			else if (current_cell == 4) {
				if (c4.symbol == ' ') {
					c4.symbol = p.symbol;
					switch_symbol();
				}
			}
			else if (current_cell == 5) {
				if (c5.symbol == ' ') {
					c5.symbol = p.symbol;
					switch_symbol();
				}
			}
			else if (current_cell == 6) {
				if (c6.symbol == ' ') {
					c6.symbol = p.symbol;
					switch_symbol();
				}
			}
			else if (current_cell == 7) {
				if (c7.symbol == ' ') {
					c7.symbol = p.symbol;
					switch_symbol();
				}
			}
			else if (current_cell == 8) {
				if (c8.symbol == ' ') {
					c8.symbol = p.symbol;
					switch_symbol();
				}
			}
			else if (current_cell == 9) {
				if (c9.symbol == ' ') {
					c9.symbol = p.symbol;
					switch_symbol();
				}
			}

		}
		if ( (GPIOA->IDR & (1 << 8)) == 0) // up pressed
		{			
			struct vector2d thrust = get_direction(&p);
			multiply_vector(&thrust, .06);
			apply_force(&p.velocity, thrust);
		}

		update_player(&p);
		bounds_player(&p);

		// Draws player to screen
		draw_player(&p);
		draw_board();
		draw_symbol(&c1);
		draw_symbol(&c2);
		draw_symbol(&c3);
		draw_symbol(&c4);
		draw_symbol(&c5);
		draw_symbol(&c6);
		draw_symbol(&c7);
		draw_symbol(&c8);
		draw_symbol(&c9);

		// Current player, to be replaced by external indicator i think
		printText(&p.symbol, 10, 10, RGBToWord(255, 255, 255), 0);

		if (check_win()) {
			printTextX2("A player wins!", 10, 60, RGBToWord(255, 255, 255), 0);
		}
		
		// Adds slight delay so that the game doesnt run like its on steroids
		delay(30);
	}
	return 0;
}

void initSysTick(void)
{
	SysTick->LOAD = 48000;
	SysTick->CTRL = 7;
	SysTick->VAL = 10;
	__asm(" cpsie i "); // enable interrupts
}

void SysTick_Handler(void)
{
	milliseconds++;
}

void initClock(void)
{
// This is potentially a dangerous function as it could
// result in a system with an invalid clock signal - result: a stuck system
        // Set the PLL up
        // First ensure PLL is disabled
        RCC->CR &= ~(1u<<24);
        while( (RCC->CR & (1 <<25))); // wait for PLL ready to be cleared
        
// Warning here: if system clock is greater than 24MHz then wait-state(s) need to be
// inserted into Flash memory interface
				
        FLASH->ACR |= (1 << 0);
        FLASH->ACR &=~((1u << 2) | (1u<<1));
        // Turn on FLASH prefetch buffer
        FLASH->ACR |= (1 << 4);
        // set PLL multiplier to 12 (yielding 48MHz)
        RCC->CFGR &= ~((1u<<21) | (1u<<20) | (1u<<19) | (1u<<18));
        RCC->CFGR |= ((1<<21) | (1<<19) ); 

        // Need to limit ADC clock to below 14MHz so will change ADC prescaler to 4
        RCC->CFGR |= (1<<14);

        // and turn the PLL back on again
        RCC->CR |= (1<<24);        
        // set PLL as system clock source 
        RCC->CFGR |= (1<<1);
}

void delay(volatile uint32_t dly)
{
	uint32_t end_time = dly + milliseconds;
	while(milliseconds != end_time)
		__asm(" wfi "); // sleep
}

void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber)
{
	Port->PUPDR = Port->PUPDR &~(3u << BitNumber*2); // clear pull-up resistor bits
	Port->PUPDR = Port->PUPDR | (1u << BitNumber*2); // set pull-up bit
}

void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode)
{
	/*
	*/
	uint32_t mode_value = Port->MODER;
	Mode = Mode << (2 * BitNumber);
	mode_value = mode_value & ~(3u << (BitNumber * 2));
	mode_value = mode_value | Mode;
	Port->MODER = mode_value;
}

// Returns 1 if inside, else 0
int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py)
{
	// checks to see if point px,py is within the rectange defined by x,y,w,h
	uint16_t x2,y2;
	x2 = x1+w;
	y2 = y1+h;
	int rvalue = 0;
	if ( (px >= x1) && (px <= x2))
	{
		// ok, x constraint met
		if ( (py >= y1) && (py <= y2))
			rvalue = 1;
	}
	return rvalue;
}

void setupIO()
{
	RCC->AHBENR |= (1 << 18) + (1 << 17); // enable Ports A and B
	display_begin();
	pinMode(GPIOB,4,0);
	pinMode(GPIOB,5,0);
	pinMode(GPIOA,8,0);
	pinMode(GPIOA,11,0);
	enablePullUp(GPIOB,4);
	enablePullUp(GPIOB,5);
	enablePullUp(GPIOA,11);
	enablePullUp(GPIOA,8);
}

// Function returns 0 if not in a cell, 1 -> 9 being cell numbers (3 top right, 7 bottom left etc)
// Draw rectangle was meant to highlight current cell but would require redrawing over previous cells and thats a nightmare i dont have time to deal with
// It was also not drawing correctly lmao. a bit off centre, prob an easy fix somewhere if i went to look for it
int check_current_cell() {
	if (isInside(c1.top_left.x, c1.top_left.y, (c1.top_right.x - c1.top_left.x), (c1.bottom_left.y - c1.top_left.y), p.location.x, p.location.y)) {
		return 1;
		//drawRectangle(c1.top_left.x - 5, c1.top_left.y - 5, ((c1.top_right.x - c1.top_left.x) - 5), ((c1.bottom_left.y - c1.top_left.y) - 5), 0xFFFF00);
	}
	else if (isInside(c2.top_left.x, c2.top_left.y, (c2.top_right.x - c2.top_left.x), (c2.bottom_left.y - c2.top_left.y), p.location.x, p.location.y)) {
		return 2;
		//drawRectangle(c2.top_left.x - 5, c2.top_left.y - 5, ((c2.top_right.x - c2.top_left.x) - 5), ((c2.bottom_left.y - c2.top_left.y) - 5), 0xFFFF00);
	}
	else if (isInside(c3.top_left.x, c3.top_left.y, (c3.top_right.x - c3.top_left.x), (c3.bottom_left.y - c3.top_left.y), p.location.x, p.location.y)) {
		return 3;
		//drawRectangle(c3.top_left.x - 5, c3.top_left.y - 5, ((c3.top_right.x - c3.top_left.x) - 5), ((c3.bottom_left.y - c3.top_left.y) - 5), 0xFFFF00);
	}
	else if (isInside(c4.top_left.x, c4.top_left.y, (c4.top_right.x - c4.top_left.x), (c4.bottom_left.y - c4.top_left.y), p.location.x, p.location.y)) {
		return 4;
		//drawRectangle(c4.top_left.x - 5, c4.top_left.y - 5, ((c4.top_right.x - c4.top_left.x) - 5), ((c4.bottom_left.y - c4.top_left.y) - 5), 0xFFFF00);
	}
	else if (isInside(c5.top_left.x, c5.top_left.y, (c5.top_right.x - c5.top_left.x), (c5.bottom_left.y - c5.top_left.y), p.location.x, p.location.y)) {
		return 5;
		//drawRectangle(c5.top_left.x - 5, c5.top_left.y - 5, ((c5.top_right.x - c5.top_left.x) - 5), ((c5.bottom_left.y - c5.top_left.y) - 5), 0xFFFF00);
	}
	else if (isInside(c6.top_left.x, c6.top_left.y, (c6.top_right.x - c6.top_left.x), (c6.bottom_left.y - c6.top_left.y), p.location.x, p.location.y)) {
		return 6;
		//drawRectangle(c6.top_left.x - 5, c6.top_left.y - 5, ((c6.top_right.x - c6.top_left.x) - 5), ((c6.bottom_left.y - c6.top_left.y) - 5), 0xFFFF00);
	}
	else if (isInside(c7.top_left.x, c7.top_left.y, (c7.top_right.x - c7.top_left.x), (c7.bottom_left.y - c7.top_left.y), p.location.x, p.location.y)) {
		return 7;
		//drawRectangle(c7.top_left.x - 5, c7.top_left.y - 5, ((c7.top_right.x - c7.top_left.x) - 5), ((c7.bottom_left.y - c7.top_left.y) - 5), 0xFFFF00);
	}
	else if (isInside(c8.top_left.x, c8.top_left.y, (c8.top_right.x - c8.top_left.x), (c8.bottom_left.y - c8.top_left.y), p.location.x, p.location.y)) {
		return 8;
		//drawRectangle(c8.top_left.x - 5, c8.top_left.y - 5, ((c8.top_right.x - c8.top_left.x) - 5), ((c8.bottom_left.y - c8.top_left.y) - 5), 0xFFFF00);
	}
	else if (isInside(c9.top_left.x, c9.top_left.y, (c9.top_right.x - c9.top_left.x), (c9.bottom_left.y - c9.top_left.y), p.location.x, p.location.y)) {
		return 9;
		//drawRectangle(c9.top_left.x - 5, c9.top_left.y - 5, ((c9.top_right.x - c9.top_left.x) - 5), ((c9.bottom_left.y - c9.top_left.y) - 5), 0xFFFF00);
	}

	return 0;
}

// Returns 1 if win
int check_win() {
	// Vertical win conditions
	if ((c1.symbol == c4.symbol) == c7.symbol && c1.symbol != ' ') {
		return 1;
	}
	else if ((c2.symbol == c5.symbol) == c8.symbol && c5.symbol != ' ') {
		printNumberX2(5, 10, 60, RGBToWord(255, 255, 255), 0);
		return 1;
	}
	else if ((c3.symbol == c6.symbol) == c9.symbol && c3.symbol != ' ') {
		return 1;
	}
	// Horizontal win conditions
	else if ((c1.symbol == c2.symbol) == c3.symbol && c1.symbol != ' ') {
		return 1;
	}
	else if ((c4.symbol == c5.symbol) == c6.symbol && c5.symbol != ' ') {
		return 1;
	}
	else if ((c7.symbol == c8.symbol) == c9.symbol && c7.symbol != ' ') {
		return 1;
	}
	// Diagonal win conditions
	else if ((c1.symbol == c5.symbol) == c9.symbol && c1.symbol != ' ') {
		return 1;
	}
	else if ((c3.symbol == c5.symbol) == c7.symbol && c5.symbol != ' ') {
		return 1;
	}
	return 0;
}

void switch_symbol() {
	if (p.symbol == 'X') {
		p.symbol = 'O';
	}
	else {
		p.symbol = 'X';
	}
}