#include <ncurses.h>
#include "draw.h"

int get_mouse_click(screen_t *screen) {

    /* Enable mouse clicks*/
    mousemask(ALL_MOUSE_EVENTS, NULL);
    keypad(screen->main_window, TRUE);

    int c = wgetch(screen->main_window);

    if(c == KEY_MOUSE) {
        MEVENT event;
        if (getmouse(&event) == OK) {
            int i, y, x, bottom_y, bottom_x;
            for(i = 0; i < screen->game->board_size; i++) {
                getparyx(screen->tiles[i], y, x);
                if(     event.y >= y && event.y < y+screen->tile_width
                     && event.x >= x && event.x < x+screen->tile_height) {
                    return i;
                }
            }
        } else {
        }
    } else {
    }
    fflush(stderr);
    return -1;
}