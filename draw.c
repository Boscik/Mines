#include "draw.h"
#include <stdlib.h>
#include <string.h>

static const tile_width = 5;
static const tile_height = 3;

void init_colors();

screen_t *init_screen(game_t *game) {
    screen_t *screen = (screen_t *)malloc(sizeof(screen_t));
    screen->tiles = (WINDOW **)malloc(game->board_size * sizeof(WINDOW *));
    screen->main_window = initscr();
    screen->game = game;

    screen->tile_width = 3;
    screen->tile_height = 5;

    int width = game->width;
    int i;
    for(i = 0; i < game->board_size; i++) {
        int y = i%width;
        int x = i/width;

        /* Create subwidow for each board tile */
        WINDOW *tile = subwin(screen->main_window, tile_height, tile_width, x*tile_height, y*tile_width);

        /* Set text of the tile */
        screen->tiles[i] = tile;
    }

    return screen;
}
void draw_state(screen_t *screen) {
    int i;

    /* If terminal supports colors */
    if(has_colors()) {
        /* Start color mode */
        start_color();
    }

    init_colors();
    for(i = 0; i < screen->game->board_size; i++) {

        char c[1];
        c[0] = screen->game->visible_board[i];

        if(c[0] == screen->game->mine_char) {
            wattron(screen->tiles[i], COLOR_PAIR(1));
        } else if(c[0] == screen->game->empy_char) {
            wattron(screen->tiles[i], COLOR_PAIR(2));
        } else if(c[0] == screen->game->unrevealed_char) {
            wattron(screen->tiles[i], COLOR_PAIR(7));
        } else {
            int color_pair_index = ((c[0]-'0')%4)+3;
            wattron(screen->tiles[i], COLOR_PAIR(color_pair_index));
        }
        /* set tile text */
        mvwaddstr(screen->tiles[i], 1, 2, c);
        
        /* Create box to draw the tile */
        box(screen->tiles[i], 0, 0);
        wrefresh(screen->tiles[i]);
    }
    wrefresh(screen->main_window);
}

void init_colors() {
    init_pair(0, COLOR_BLACK, COLOR_BLACK);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
}

void terminate_screen(screen_t *screen) {
    int i;

    delwin(screen->main_window);

    for(i = 0; i < screen->game->board_size; i++) {
        delwin(screen->tiles[i]);
    }
    free(screen->tiles);
    free(screen);
}

WINDOW *draw_result_window(int result) {
    WINDOW *result_window = initscr();
    /* clear artifacts from previous windows*/
    wclear(result_window);

    int y, x;
    getmaxyx(result_window, y, x);

    char * result_string;
    result_string = (result == GAME_WON) ? "Game won" : "Game lost";
    
    box(result_window, 0, 0);
    /* add centered string */
    mvwaddstr(result_window, y/2, (x-strlen(result_string))/2, result_string);
    return result_window;
}

void terminate_result_window(WINDOW *window) {
    delwin(window);
}