// board.h

#define CELL_SIZE 35

struct position {
    int x;
    int y;
};

struct cell {
    struct position centre;
    struct position top_left;
    struct position top_right;
    struct position bottom_left;
    struct position bottom_right;
    char symbol;
};

void draw_board();
void draw_symbol(struct cell* c);
int check_current_cell();
