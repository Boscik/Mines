#ifndef DRAW_H
#define DRAW_H

#include "game.h"
#include <ncurses.h>

typedef struct screen {
    WINDOW * main_window;
    WINDOW ** tiles;
    int tile_width;
    int tile_height;

    game_t *game;
} screen_t;

screen_t *init_screen(game_t *game);
void draw_state(screen_t *screen);
void terminate_screen(screen_t *screen);

#endif