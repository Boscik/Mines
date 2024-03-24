#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE (16*8)

static const int width = 16;
static const int height = 8;

static const int tile_size = 3;
char board[BOARD_SIZE];

void set_board(char c) {
    int i;
    for(i = 0; i < sizeof(board)/sizeof(char); i++) {
        board[i] = c;
    }
}

void set_mines(WINDOW * win, int arg_count) {
    srand(time(NULL));

    set_board(' ');

    int counter = 0;
    while (counter < arg_count) {
        int pos = rand() % (width*height + 1);
        if(board[pos] != 'x') {
            board[pos] = 'x';
            counter++;
        }
        
        /* WINDOW * tile = subwin(win, tile_size, tile_size, (pos%height)*tile_size, (pos/height)*tile_size);
        box(tile, 0, 0);
        mvwaddstr(tile, 1, 1, "x"); */
    }
}

int main(int argc, char *argv[]) {
    WINDOW * mainwin = initscr();
    /* WINDOW * menu = subwin(mainwin, 3, 10, 0, 0); */

    /* WINDOW * board = subwin(mainwin, 0, 0, 3, 10); */

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

    set_mines(mainwin, 8);

    int i;
    for(i = 0; i < width*height; i++) {
        int y = i%width;
        int x = i/width;

        char c[1];
        c[0] = board[i];

        /* printf("\r%d - %d\n", y, x); */

        /* Create subwidow for each board tile */
        WINDOW * tile = subwin(mainwin, tile_size, tile_size, x*tile_size, y*tile_size);
        /* Create box to draw the tile */
        box(tile, 0, 0);
        /* Set text of the tile */
        mvwaddstr(tile, 1, 1, c);
    }

    
    refresh();
    getch();
    sleep(30);
    endwin();
    echo();
}

