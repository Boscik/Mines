#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

static const int width = 8;
static const int height = 10;

static const int tile_size = 3;

void set_bombs(WINDOW * win, int arg_count) {
    srand(time(NULL));
    int i;
    for(i = 0; i < arg_count; i++) {
        int pos = rand() % (width*height + 1);
        WINDOW * tile = subwin(win, tile_size, tile_size, (pos%height)*tile_size, (pos/height)*tile_size);
        printf("\r %d %d\n", (pos%height)*tile_size, (pos%height)*tile_size);
        box(tile, 0, 0);
        mvwaddstr(tile, 1, 1, "x");
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

    int i;
    int j;
    for(i = 0; i < width; i++) {
        for(j = 0; j < height; j++) {
            /* // Create subwidow for each board tile 
            // WINDOW * tile = subwin(mainwin, tile_size, tile_size, j*tile_size, i*tile_size);
            // Create box to draw the tile
            // box(tile, 0, 0);
            // Set text of the tile
            // mvwaddstr(tile, 1, 1, "x"); */
        }
    }
    set_bombs(mainwin, 8);
    refresh();
    getch();
    endwin();
    echo();
}

