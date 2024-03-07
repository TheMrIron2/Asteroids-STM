#include <stm32f031x6.h>
#include <stdio.h>
#include <math.h>
#include "../assets/assets.h"
#include "display.h"
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
	
	// Degree of rotation, from -1 -> 1
	float direction = 0;

	int toggle = 0;
	int hmoved = 0;
	int vmoved = 0;

	// X position of the player
	uint16_t x = 50;
	// Y position of the player
	uint16_t y = 50;

	uint16_t oldx = x;
	uint16_t oldy = y;
	initClock();
	initSysTick();
	setupIO();
	putImage(20,80,12,16,dg1,0,0);
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
			double angleRadians = direction * (3.141592653589) / 180.0;

			// Calculate change in x and y using trigonometric functions
			x = x + (2 * cos(angleRadians));
			y = y + (2 * sin(angleRadians));
			vmoved = 1;
			hmoved = 1;
		}
		
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
				putImage(x,y,16,16,player_,hinverted,0);
			}
			else
			{
				putImage(x,y,16,16,player,0,vinverted);
			}
			// Now check for an overlap by checking to see if ANY of the 4 corners of deco are within the target area
			if (isInside(20,80,12,16,x,y) || isInside(20,80,12,16,x+12,y) || isInside(20,80,12,16,x,y+16) || isInside(20,80,12,16,x+12,y+16) )
			{
				printText("DEAN IS", 10, 100, RGBToWord(0xff,0xff,0), 0);
				printText("A BOZO", 10, 115, RGBToWord(0xff,0,0), 0);
			}
		}
		printNumber(x, 10, 10, RGBToWord(0xff, 0xff, 0xff), 0);
		printNumber(y, 10, 20, RGBToWord(0xff, 0xff, 0xff), 0);
		printNumber((direction), 10, 30, RGBToWord(0xff, 0xff, 0xff), 0);
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