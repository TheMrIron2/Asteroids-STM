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

volatile uint32_t milliseconds;

// The player
struct player p;

int main()
{
	// Starts clocks and system processes
	initClock();
	initSound();
	initSysTick();
	setupIO();
	init_player(&p);

	bool menu = 1;

	// X position of the asteroid
	uint16_t asteroid_x = 2;
	// Y position of the asteroid
	uint16_t asteroid_y = 120; 

	// Title text
	printTextX2("Tic-Tac-Toe", 10, 10, RGBToWord(0xff,0xff,0), 0);
	printTextX2("But", 10, 30, RGBToWord(0xff,0xff,0), 0);
	printTextX2("Worse", 10, 50, RGBToWord(0xff,0xff,0), 0);
	printText("Press right", 30, 100, RGBToWord(0xff,0xff,0), 0);
	draw_player(&p);

	while(menu == 1)
	{
		putImage(asteroid_x,asteroid_y,16,16,asteroid,0,0);
		asteroid_x = asteroid_x + 1;

		if ((GPIOB->IDR & (1 << 4))==0) // right pressed
		{					
			menu = 0;
			fillRectangle(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		}
		delay(50);
	}

	int start_txt_x = 30;
	int start_txt_y = 100;
	printText("Start Game", start_txt_x, start_txt_y, RGBToWord(0xff,0xff,0), 0);

	int quit = 0;

	while(quit == 0)
	{
		
		if ((GPIOB->IDR & (1 << 4))==0) // right pressed
		{					
			rotate_player(&p, 6);
			playNote(440);
			
		}
		if ((GPIOB->IDR & (1 << 5))==0) // left pressed
		{			
			rotate_player(&p, -6);
		}
		if ( (GPIOA->IDR & (1 << 11)) == 0) // down pressed
		{
			// Check box with current letter
		}
		if ( (GPIOA->IDR & (1 << 8)) == 0) // up pressed
		{			
			struct vector2d thrust = get_direction(&p);
			multiply_vector(&thrust, .06);
			apply_force(&p.velocity, thrust);
		}

		// Draws player to screen
		draw_player(&p);
		draw_board();

		update_player(&p);
		bounds_player(&p);
		
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