#include <ncurses.h>
#include "draw.h"

int get_mouse_click(screen_t *screen) {
    /* TODO tmp */
    FILE *f = fopen("output/log.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        return -1;
    }
    /* tmp */

    /* Enable mouse clicks*/
    mousemask(ALL_MOUSE_EVENTS, NULL);
    keypad(screen->main_window, TRUE);

    int c = wgetch(screen->main_window);

    if(c == KEY_MOUSE) {
        MEVENT event;
        if (getmouse(&event) == OK) {
            fprintf(f, "\rEvent position %i %i\n", event.y, event.x);
            int i, y, x, bottom_y, bottom_x;
            for(i = 0; i < screen->game->board_size; i++) {
                getparyx(screen->tiles[i], y, x);
                if(     event.y >= y && event.y < y+screen->tile_width
                     && event.x >= x && event.x < x+screen->tile_height) {
                    fprintf(f, "\rTile position %i %i -- %i %i\n", y, x, y+screen->tile_width, x+screen->tile_height);
                    fprintf(f, "\rChar on a tile %c\n", screen->game->board[i]);

                    fprintf(f, "\rIndex in 1-D array %i\n", i);
                    
                    fclose(f);
                    return i;
                }
            }
        } else {
            fprintf(f, "Mouse event error\n");
        }
    } else {
        fprintf(f, "wrong char\n");
    }
    fflush(stderr);
    fclose(f);
    return -1;
}