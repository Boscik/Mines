#include <stdlib.h>

#include "game.h"
#include "draw.h"
#include "controller.h"

static const int width = 5;
static const int height = 5;
static const int board_size = width*height;

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


    int position;
    do {
        draw_state(screen);
        refresh();
        position = get_mouse_click(screen);
    } while (play_position(game, position));

    refresh();
    
    echo();
    endwin();

    terminate_screen(screen);
    terminate_game(game);
    
    return 0;
}

