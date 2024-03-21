// board.c

#include <stdio.h>
#include "display.h"
#include "board.h"

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