#include <stdlib.h>
#include <string.h>

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
    if(width < 0 || height < 0) {
        fprintf(stderr, "Invalid dimensions\n");
        return 1;
    }
    if(mine_count > width*height) {
        fprintf(stderr, "Number of mines must be lower or equal to the board size\n");
        return 1;
    }

    /* dont print key pressses */
    noecho();

    game_t *game = init_game(width, height, mine_count);
    screen_t *screen = init_screen(game);

    draw_state(screen);

    int position, result;
    int exit = 0;
    while ((result = is_game_finished(game)) == 0) {
        position = get_mouse_click(screen, &exit);
        if(exit) break;
        if(position == -1) continue; /* invalid input */

        play_position(game, position);
        draw_state(screen);
    }

    if(!exit) getch();

    echo();

    terminate_screen(screen);
    terminate_game(game);

    WINDOW *result_window =  draw_result_window(result);
    if(!exit) getch();
    
    terminate_result_window(result_window);
    
    endwin();

    return 0;
}

