#include <stm32f031x6.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "../assets/assets.h"
#include "musical_notes.h"
#include "sound.h"
#include "display.h"
#include "player.h"

void initClock(void);
void initSysTick(void);
void SysTick_Handler(void);
void delay(volatile uint32_t dly);
void setupIO();
int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py);
void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber);
void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode);

volatile uint32_t milliseconds;

int main()
{
	int hinverted = 0;
	int vinverted = 0;
	
	// Degree of rotation, from 0 -> 360
	float direction = 0;

	//int toggle = 0; // unused
	int hmoved = 0;
	int vmoved = 0;

	// X position of the player
	uint16_t x = 50;
	// Y position of the player
	uint16_t y = 50;

	// Delta X speed of the player
	float delta_x = 0;
	// Delta Y speed of the player
	float delta_y = 0;

	uint16_t oldx = x;
	uint16_t oldy = y;
	initClock();
	initSound();
	initSysTick();
	setupIO();

	bool menu = 1;

	printText("Press right", 10, 100, RGBToWord(0xff,0xff,0), 0);

	while(menu == 1)
	{
		if ((GPIOB->IDR & (1 << 4))==0) // right pressed
		{					
			menu = 0;
			fillRectangle(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, 0x0);
		}
	}

	bool game_started = 0;	
	const char *startText="Start Game";
	int start_txt_x = 30;
	int start_txt_y = 100;
	printText(startText, start_txt_x, start_txt_y, RGBToWord(0xff,0xff,0), 0);
	int start_txt_len=(int) mystrlen(startText);
	int start_txt_width = start_txt_len * 7; // characters are 5 pixels + 2 for space
    int start_txt_height = 7;

	putImage(x,y,16,16,player_90,0,0);
	while(1)
	{
		if (direction > 360) {
			direction = direction - 360;
		}
		if (direction < 0) {
			direction = direction + 360;
		}
		hmoved = vmoved = 0;
		//hinverted = vinverted = 0;
		if ((GPIOB->IDR & (1 << 4))==0) // right pressed
		{					
			direction = direction + 10;
			hmoved = 1;	
			playNote(440);
			
		}
		if ((GPIOB->IDR & (1 << 5))==0) // left pressed
		{			
			direction = direction - 10;
			hmoved = 1;	
		}
		/*if ( (GPIOA->IDR & (1 << 11)) == 0) // down pressed
		{
			
		}*/
		if ( (GPIOA->IDR & (1 << 8)) == 0) // up pressed
		{			
			// Convert angle to radians
			double angleRadians = direction * ((3.142) / 180.0);

			// Calculate change in x and y using trigonometric functions
			delta_x = delta_x + (1 * cos(angleRadians));
			delta_y = delta_y + (1 * sin(angleRadians));
			
			vmoved = 1;
			hmoved = 1;
		}
		else {
			if (delta_x > 0) {
				delta_x = delta_x - 1;
			}
			if (delta_y > 0) {
				delta_y = delta_y - 1;
			}

		}

		x += delta_x;
		y += delta_y;

		//drawRectangle((x + delta_x), (y + delta_y), 3, 3, RGBToWord(0xff, 0, 0)); attempt at debug square
		
		// Wraps screen
		if (y < 2)
		{
			y = 140;
		}
		if (y > 140)
		{
			y = 1;
		}
		if (x < 2)
		{
			x = 120;
		}
		if (x > 120)
		{
			x = 1;
		}

		if ((vmoved) || (hmoved))
		{
			// only redraw if there has been some movement (reduces flicker)
			fillRectangle(oldx,oldy,12,16,0);
			oldx = x;
			oldy = y;					
			if (hmoved) // sprites displayed with this function have an issue if hinverted is removed...
			{
				putImage(x,y,16,16,player_90,hinverted,0);
			}
			else
			{
				putImage(x,y,16,16,player,0,vinverted);
			}
			// Now check for an overlap by checking to see if ANY of the 4 corners of deco are within the target area
			if (game_started)
			{
			// Draw asteroids
			}
			else
			{
				if (isInside(start_txt_x, start_txt_y, start_txt_width, start_txt_height,x,y) 
					|| isInside(start_txt_x, start_txt_y, start_txt_width, start_txt_height,x+12,y) 
					|| isInside(start_txt_x, start_txt_y, start_txt_width, start_txt_height,x,y+16) 
					|| isInside(start_txt_x, start_txt_y, start_txt_width, start_txt_height,x+12,y+16) )
				{
					game_started = 1;
					fillRectangle(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, 0x0);
					printText("DEAN IS", 10, 100, RGBToWord(0xff,0xff,0), 0);
					printText("A BOZO", 10, 115, RGBToWord(0xff,0,0), 0);
				}
			}

		}
		printNumber(x, 10, 10, RGBToWord(0xff, 0xff, 0xff), 0);
		printNumber(y, 10, 20, RGBToWord(0xff, 0xff, 0xff), 0);
		printNumber(direction, 10, 30, RGBToWord(0xff, 0xff, 0xff), 0);
		printNumber(delta_x, 10, 40, RGBToWord(0xff, 0xff, 0xff), 0);
		printNumber(delta_y,  10, 50, RGBToWord(0xff, 0xff, 0xff), 0);
		printText("X POS", 50, 10, RGBToWord(0xff,0xff,0), 0);
		printText("Y POS", 50, 20, RGBToWord(0xff,0xff,0), 0);
		printText("DIR", 50, 30, RGBToWord(0xff,0xff,0), 0);
		printText("DELTA X", 50, 40, RGBToWord(0xff,0xff,0), 0);
		printText("DELTA Y", 50, 50, RGBToWord(0xff,0xff,0), 0);
		delay(50);
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