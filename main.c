#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE (5*5)

static const int width = 5;
static const int height = 5;

static const int tile_size = 3;
char board[BOARD_SIZE];

void set_numbers_around(int arg_pos) {
    int k;
    int i;
    for(k = arg_pos-width; k <= arg_pos+width; k += width)
    {
        /* printf("\rk = %d\n", k); */
        for(i = k-1; i <= k + 1; i++) {
            /* check if we are in bounds */
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
    for(i = 0; i < sizeof(board)/sizeof(char); i++) {
        /* board[i] = (i%('z'-'a'+1)+'a'); */
        board[i] = c;
    }
}

void set_mines(WINDOW * win, int arg_count) {
    srand(time(NULL));

    set_board('0');

    int counter = 0;
    while (counter < arg_count) {
        int pos = rand() % (width*height);
        if(board[pos] != 'x') {
            board[pos] = 'x';
            set_numbers_around(pos);
            counter++;
            printf("\rpos %d\n", pos);
        }
        /* printf("\rCounter %d\n", counter); */
    }
}

int main(int argc, char *argv[]) {
    WINDOW * mainwin = initscr();

    /* dont print key pressses */
    noecho();

    /* If terminal supports colors */
    if(has_colors() == TRUE) {
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

    int i;
    for(i = 0; i < width*height; i++) {
        int y = i%width;
        int x = i/width;

        char c[1];
        c[0] = board[i];

        /* Create subwidow for each board tile */
        WINDOW * tile = subwin(mainwin, tile_size, tile_size+2, x*tile_size, y*(tile_size+2));

        if(c[0] == 'x') {
            wattron(tile, COLOR_PAIR(2));
        } else {
            wattron(tile, COLOR_PAIR(c[0]-'0'+3));
            printf("\r%d\n", c[0]-'0'+3);
        }

        /* Create box to draw the tile */
        box(tile, 0, 0);

        /* Set text of the tile */
        mvwaddstr(tile, 1, 2, c);
    }

    refresh();
    getch();
    endwin();
    echo();
}

