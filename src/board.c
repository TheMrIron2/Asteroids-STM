// board.c

#include <stdio.h>
#include "display.h"
#include "board.h"

// The cells
struct cell c1, c2, c3, c4, c5, c6, c7, c8, c9;

// Gets passed a cell and if it shouldn't be blank, draws either an X or an O
void draw_symbol(struct cell* c) {
    if (c->symbol == ' ') {
        return;
    }
    else if (c->symbol == 'X') {
        // Change the 10s here to change the size of the X, it's all centred on the centre of the cell
        drawLine((c->centre.x + 10), (c->centre.y + 10), (c->centre.x - 10), (c->centre.y - 10), RGBToWord(255, 0, 0));
        drawLine((c->centre.x - 10), (c->centre.y + 10), (c->centre.x + 10), (c->centre.y - 10), RGBToWord(255, 0, 0));
    }
    else if (c->symbol == 'O') {
        // Draws a circle centred on the centre of the cell
        drawCircle(c->centre.x, c->centre.y, 13, RGBToWord(0, 255, 0));
    }
    
}

// Draws four lines on screen 
void draw_board() {
    // Draws the lines for the board. It uses so much math because I can now change the size of the board modularly by just changing the value of CELL_SIZE.
    drawLine((SCREEN_CENTRE_X - (CELL_SIZE / 2)), (SCREEN_CENTRE_Y - (CELL_SIZE + (CELL_SIZE / 2))), ((SCREEN_CENTRE_X) - (CELL_SIZE / 2)), (SCREEN_CENTRE_Y + (CELL_SIZE + (CELL_SIZE / 2))), RGBToWord(255, 255, 255));
    drawLine((SCREEN_CENTRE_X + (CELL_SIZE / 2)), (SCREEN_CENTRE_Y - (CELL_SIZE + (CELL_SIZE / 2))), ((SCREEN_CENTRE_X) + (CELL_SIZE / 2)), (SCREEN_CENTRE_Y + (CELL_SIZE + (CELL_SIZE / 2))), RGBToWord(255, 255, 255));
    drawLine((SCREEN_CENTRE_X - (CELL_SIZE + (CELL_SIZE / 2))), (SCREEN_CENTRE_Y - (CELL_SIZE / 2)), ((SCREEN_CENTRE_X) + (CELL_SIZE + (CELL_SIZE / 2))), (SCREEN_CENTRE_Y - (CELL_SIZE / 2)), RGBToWord(255, 255, 255));
    drawLine((SCREEN_CENTRE_X - (CELL_SIZE + (CELL_SIZE / 2))), (SCREEN_CENTRE_Y + (CELL_SIZE / 2)), ((SCREEN_CENTRE_X) + (CELL_SIZE + (CELL_SIZE / 2))), (SCREEN_CENTRE_Y + (CELL_SIZE / 2)), RGBToWord(255, 255, 255));

}

// Initialise the cells. Could have been implemented with loops and array - but this solution worked fine!
// Refactoring it broke other parts of the game and would have taken a lot of time without benefit.
void initBoard()
{
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
}