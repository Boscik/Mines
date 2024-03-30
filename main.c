#include <stdlib.h>

#include "game.h"
#include "draw.h"

static const int width = 5;
static const int height = 5;
static const int board_size = width*height;

static const int tile_size = 3;
char *board;
WINDOW **tiles; 

void set_numbers_around(int arg_pos) {
    int k;
    int i;
    /* TODO */
    for(k = arg_pos-width; k <= arg_pos+width; k += width) {
        /* check bounds */
        if(k < 0 || k >= board_size) continue;

        for(i = k-1; i <= k + 1; i++) {
            /* check if line didn't overflow/underflow */
            if(k/width != i/width) continue;

            /* check bounds */
            if(i >= 0 && i != arg_pos) {
                if(board[i] != 'x') {
                    board[i]++;
                    printf("\rsetting number on board %c\n", board[i]);
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
}

int main(int argc, char *argv[]) {
    board = (char *)malloc(board_size * sizeof(char));
    tiles = (WINDOW **)malloc(board_size * sizeof(WINDOW *));
    WINDOW * mainwin = initscr();

    /* dont print key pressses */
    noecho();

    /* If terminal supports colors */
    if(has_colors()) {
        /* Start color mode */
        start_color();
        /* Create color pair */
        init_pair(1, COLOR_CYAN, COLOR_BLACK);
        /* Set color pair */
        attron(COLOR_PAIR(1));
    }

    set_mines(mainwin, 16);

    init_pair(2, COLOR_RED, COLOR_BLACK);

    init_pair(3, COLOR_RED+1, COLOR_BLACK);
    init_pair(4, COLOR_RED+2, COLOR_BLACK);
    init_pair(5, COLOR_RED+3, COLOR_BLACK);
    init_pair(6, COLOR_RED+4, COLOR_BLACK);
    init_pair(7, COLOR_RED+5, COLOR_BLACK);

    int i, j;
    for(i = 0; i < board_size; i++) {
        int y = i%width;
        int x = i/width;

        char c[1];
        c[0] = board[i];

        /* Create subwidow for each board tile */
        tiles[i] = subwin(mainwin, tile_size, tile_size+2, x*tile_size, y*(tile_size+2));

        if(c[0] == 'x') {
            wattron(tiles[i], COLOR_PAIR(2));
        } else {
            int color_pair_index = ((c[0]-'0')%4)+3;
            printf("\rcolor pair: %d\n", color_pair_index);
            wattron(tiles[i], COLOR_PAIR(color_pair_index));
        }

        /* Create box to draw the tile */
        box(tiles[i], 0, 0);

        /* Set text of the tile */
        mvwaddstr(tiles[i], 1, 2, c);
    }

    refresh();
    getch();
    endwin();
    echo();
    free(board);
    delwin(mainwin);
    for(j = 0; j < board_size; j++) {
        delwin(tiles[j]);
    }
}

