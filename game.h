#ifndef GAME_H
#define GAME_H

#define GAME_WON 1
#define GAME_LOST 2

typedef struct game {
    int board_size;
    int width;
    int height;

    int mine_count;

    char *board;
    /* TODO create two boards - one visible to the player and another for game state */
    char *visible_board;
    char mine_char;
    char empy_char;
    char unrevealed_char;

    int is_lost;
} game_t;


game_t *init_game(int width, int height, int mine_count);
int play_position(game_t *game, int position);
void terminate_game(game_t *game);
int is_game_finished(game_t *game);

#endif