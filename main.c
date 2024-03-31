#include <stdlib.h>

#include "game.h"
#include "draw.h"
#include "controller.h"

int main(int argc, char *argv[]) {
    if(argc != 4) {
        fprintf(stderr, "Wrong arguments provided\n");
        fprintf(stderr, "Run with: %s [width] [height] [number of mines]\n", argv[0]);
        return 1;
    }
    
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int mine_count = atoi(argv[3]);
    if(mine_count > width*height) {
        fprintf(stderr, "Number of mines must be lower or equal to the board size\n");
        return 1;
    }

    /* dont print key pressses */
    noecho();

    game_t *game = init_game(width, height, mine_count);
    screen_t *screen = init_screen(game);

    draw_state(screen);

    init_pair(2, COLOR_RED, COLOR_BLACK);

    init_pair(3, COLOR_RED+1, COLOR_BLACK);
    init_pair(4, COLOR_RED+2, COLOR_BLACK);
    init_pair(5, COLOR_RED+3, COLOR_BLACK);
    init_pair(6, COLOR_RED+4, COLOR_BLACK);
    init_pair(7, COLOR_RED+5, COLOR_BLACK);


    int position, result;
    while ((result = is_game_finished(game)) == 0) {
        position = get_mouse_click(screen);
        if(position == -1) continue; /* invalid input */

        play_position(game, position);
        draw_state(screen);
    }

    getch();

    echo();
    endwin();

    terminate_screen(screen);
    terminate_game(game);
    
    return 0;
}

