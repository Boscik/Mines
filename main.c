#include <stdlib.h>

#include "game.h"
#include "draw.h"

static const int width = 5;
static const int height = 5;
static const int board_size = width*height;

/* TODO move to draw.h */
static const int tile_size = 3;
char *board;
WINDOW **tiles; 

/* void set_numbers_around(int arg_pos) {
    int k;
    int i;
    for(k = arg_pos-width; k <= arg_pos+width; k += width) {
        if(k < 0 || k >= board_size) continue;

        for(i = k-1; i <= k + 1; i++) {
            if(k/width != i/width) continue;

            if(i >= 0 && i != arg_pos) {
                if(board[i] != 'x') {
                    board[i]++;
                }
            }
        }
    }
}

void set_board(char c) {
    int i;
    for(i = 0; i < board_size; i++) {
        board[i] = c;
    }
}

void set_mines(WINDOW * win, int arg_count) {
    srand(time(NULL));

    set_board('0');

    int counter = 0;
    while (counter < arg_count) {
        int pos = rand() % (board_size);
        if(board[pos] != 'x') {
            board[pos] = 'x';
            set_numbers_around(pos);
            counter++;
        }
    }
} */

int main(int argc, char *argv[]) {
    /* dont print key pressses */
    noecho();



    game_t *game = init_game(width, height, 3);
    screen_t *screen = init_screen(game);

    draw_state(screen);

    init_pair(2, COLOR_RED, COLOR_BLACK);

    init_pair(3, COLOR_RED+1, COLOR_BLACK);
    init_pair(4, COLOR_RED+2, COLOR_BLACK);
    init_pair(5, COLOR_RED+3, COLOR_BLACK);
    init_pair(6, COLOR_RED+4, COLOR_BLACK);
    init_pair(7, COLOR_RED+5, COLOR_BLACK);

    refresh();
    getch();
    endwin();
    echo();

    terminate_screen(screen);
    terminate_game(game);
    
    free(board);
    free(tiles);

    return 0;
}

