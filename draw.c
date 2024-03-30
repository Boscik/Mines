#include "draw.h"
#include <stdlib.h>

static const tile_height = 3;
static const tile_width = 5;

screen_t *init_screen(game_t *game) {
    screen_t *screen = (screen_t *)malloc(sizeof(screen_t));
    screen->tiles = (WINDOW **)malloc(game->board_size * sizeof(WINDOW *));
    screen->main_window = initscr();
    screen->game = game;

    int width = game->width;
    int i;
    for(i = 0; i < game->board_size; i++) {
        int y = i%width;
        int x = i/width;

        /* TODO refactor */
        char c[1];
        c[0] = game->board[i];

        /* Create subwidow for each board tile */
        WINDOW *tile = subwin(screen->main_window, tile_height, tile_width, x*tile_height, y*tile_width);

        if(c[0] == 'x') {
            wattron(tile, COLOR_PAIR(2));
        } else {
            int color_pair_index = ((c[0]-'0')%4)+3;
            wattron(tile, COLOR_PAIR(color_pair_index));
        }

        /* Create box to draw the tile */
        box(tile, 0, 0);

        /* Set text of the tile */
        mvwaddstr(tile, 1, 2, c);
        screen->tiles[i] = tile;
    }
    return screen;
}
void draw_state(screen_t *screen) {}
void terminate_screen(screen_t *screen) {
    int i;

    delwin(screen->main_window);

    for(i = 0; i < screen->game->board_size; i++) {
        delwin(screen->tiles[i]);
    }
}