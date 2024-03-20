// board.c

#include <stdio.h>
#include "display.h"

#define square_size 35

void draw_board() {

    drawLine(((SCREEN_WIDTH / 2) - (square_size / 2)), ((SCREEN_HEIGHT / 2) - (square_size + (square_size / 2))), ((SCREEN_WIDTH / 2) - (square_size / 2)), ((SCREEN_HEIGHT / 2) + (square_size + (square_size / 2))), 0xfff);
    drawLine(((SCREEN_WIDTH / 2) + (square_size / 2)), ((SCREEN_HEIGHT / 2) - (square_size + (square_size / 2))), ((SCREEN_WIDTH / 2) + (square_size / 2)), ((SCREEN_HEIGHT / 2) + (square_size + (square_size / 2))), 0xfff);
    drawLine(((SCREEN_WIDTH / 2) - (square_size + (square_size / 2))), ((SCREEN_HEIGHT / 2) - (square_size / 2)), ((SCREEN_WIDTH / 2) + (square_size + (square_size / 2))), ((SCREEN_HEIGHT / 2) - (square_size / 2)), 0xfff);
    drawLine(((SCREEN_WIDTH / 2) - (square_size + (square_size / 2))), ((SCREEN_HEIGHT / 2) + (square_size / 2)), ((SCREEN_WIDTH / 2) + (square_size + (square_size / 2))), ((SCREEN_HEIGHT / 2) + (square_size / 2)), 0xfff);

}