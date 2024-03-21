// board.c

#include <stdio.h>
#include "display.h"
#include "board.h"

void draw_symbol(struct cell* c) {
    if (c->symbol == ' ') {
        return;
    }
    else if (c->symbol == 'O') {
        drawCircle(c->centre.x, c->centre.y, 15, 0xFF0000);
    }
    else if (c->symbol == 'X') {
        drawLine((c->centre.x + 10), (c->centre.y + 10), (c->centre.x - 10), (c->centre.y - 10), 0x00FF00);
        drawLine((c->centre.x - 10), (c->centre.y + 10), (c->centre.x + 10), (c->centre.y - 10), 0x00FF00);
    }
}

void draw_board() {

    // Draws the lines for the board. It uses so much math because I can now change the size of the board modularly by just changing the value of CELL_SIZE.
    drawLine((SCREEN_CENTRE_X - (CELL_SIZE / 2)), (SCREEN_CENTRE_Y - (CELL_SIZE + (CELL_SIZE / 2))), ((SCREEN_CENTRE_X) - (CELL_SIZE / 2)), (SCREEN_CENTRE_Y + (CELL_SIZE + (CELL_SIZE / 2))), 0xffffff);
    drawLine((SCREEN_CENTRE_X + (CELL_SIZE / 2)), (SCREEN_CENTRE_Y - (CELL_SIZE + (CELL_SIZE / 2))), ((SCREEN_CENTRE_X) + (CELL_SIZE / 2)), (SCREEN_CENTRE_Y + (CELL_SIZE + (CELL_SIZE / 2))), 0xffffff);
    drawLine((SCREEN_CENTRE_X - (CELL_SIZE + (CELL_SIZE / 2))), (SCREEN_CENTRE_Y - (CELL_SIZE / 2)), ((SCREEN_CENTRE_X) + (CELL_SIZE + (CELL_SIZE / 2))), (SCREEN_CENTRE_Y - (CELL_SIZE / 2)), 0xffffff);
    drawLine((SCREEN_CENTRE_X - (CELL_SIZE + (CELL_SIZE / 2))), (SCREEN_CENTRE_Y + (CELL_SIZE / 2)), ((SCREEN_CENTRE_X) + (CELL_SIZE + (CELL_SIZE / 2))), (SCREEN_CENTRE_Y + (CELL_SIZE / 2)), 0xffffff);

}