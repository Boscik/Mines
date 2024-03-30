#ifndef GAME_H
#define GAME_H

typedef struct game {
    int board_size;
    int width;
    int height;

    int mine_count;

    char *board;
    char mine_char;
    char empy_char;
} game_t;


game_t *init_game(int width, int height, int mine_count);
void play_position(game_t *game, int arg_pos);
void terminate_game(game_t *game);

#endif