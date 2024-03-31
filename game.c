#include "game.h"
#include <stdlib.h>

void set_board_to(game_t *game, char *board, char c);
void set_mines(game_t *game, int mine_count);
void set_numbers_around(game_t *game, int position);
void reveal_board(game_t *game);
void reveal_tiles_around(game_t *game, int position, short *checked_tiles);

game_t *init_game(int width, int height, int mine_count) {
    game_t *game = (game_t *)malloc(sizeof(game_t));
    
    game->board_size = width*height;
    game->width = width;
    game->height = height;
    game->mine_count = mine_count;
    
    game->board = (char *)malloc(game->board_size * sizeof(char));
    game->visible_board = (char *)malloc(game->board_size * sizeof(char));

    game->mine_char = 'x';
    game->empy_char = '_';
    game->unrevealed_char = ' ';

    game->is_lost = 0;

    set_board_to(game, game->board, game->empy_char);
    set_board_to(game, game->visible_board, game->unrevealed_char);
    set_mines(game, mine_count);

    return game;
}

void set_board_to(game_t *game, char *board, char c) {
    int i;
    for(i = 0; i < game->board_size; i++) {
        board[i] = c;
    }
}

void set_mines(game_t *game, int mine_count) {
    srand(time(NULL));

    int counter = 0;
    while (counter < mine_count) {
        /* random position for mine */
        int pos = rand() % (game->board_size);
        if(game->board[pos] != game->mine_char) {
            game->board[pos] = game->mine_char;
            /* increment numbers around new mine */
            set_numbers_around(game, pos);
            /* counter is incremented only if new mine was placed */
            counter++;
        }
    }
}

void set_numbers_around(game_t *game, int position) {
    int k, i;
    int width = game->width;
    int board_size = game->board_size;

    for(k = position-width; k <= position+width; k += width) {
        /* check bounds */
        if(k < 0 || k >= board_size) continue;

        for(i = k-1; i <= k + 1; i++) {
            /* check if line didn't overflow/underflow */
            if(k/width != i/width) continue;

            /* check bounds */
            if(i >= 0 && i <= board_size && i != position) {
                
                if(game->board[i] != game->mine_char) {
                    if(game->board[i] == game->empy_char) {
                        /* if tile is empty set it to one */
                        game->board[i] = '1';
                    } else {
                        /* otherwise incremet it */
                        game->board[i]++;
                    }
                }
            }
        }
    }
}

int play_position(game_t *game, int position) {
    if(game->board[position] == game->mine_char) {
        game->is_lost = 1;
        reveal_board(game);
    } else {
        /* game->visible_board[position] =  game->board[position]; */
        short *checked_tiles = (short *)malloc(game->board_size*sizeof(short));
        int i;
        for(i = 0; i < game->board_size; i++) {
            checked_tiles[i] = 0;
        }
        reveal_tiles_around(game, position, checked_tiles);
        free(checked_tiles);
    }
    return 1;
}

void reveal_tiles_around(game_t *game, int position, short *checked_tiles) {
    if(game->board[position] == game->empy_char) {
        game->visible_board[position] =  game->board[position];
        checked_tiles[position] = 1;

        /* TODO rewrite into a function*/
        int board_size = game->board_size;
        int width = game->width;
        int k, i;

        for(k = position-width; k <= position+width; k += width) {

            /* check bounds */
            if(k < 0 || k >= board_size) continue;

            for(i = k-1; i <= k + 1; i++) {
                /* check if line didn't overflow/underflow */
                if(k/width != i/width) continue;

                /* check bounds */
                if(i >= 0 && i <= board_size && i != position && !checked_tiles[i]) {
                    reveal_tiles_around(game, i, checked_tiles);
                }
            }
        }
    } else if (game->board[position] != game->mine_char){
        game->visible_board[position] =  game->board[position];
        checked_tiles[position] = 1;
    }
}

int is_game_finished(game_t *game) {
    int i;
    if(game->is_lost) return GAME_LOST;

    for(i = 0; i < game->board_size; i++) {
        /* dont check for mines, those should not be revealed*/
        if(game->board[i] != game->mine_char) {
            if(game->board[i] != game->visible_board[i]) {
                /* not all tiles were revealed*/
                return 0;
            }
        }
    }
    return GAME_WON;
}

void reveal_board(game_t *game) {
    int i;
    for(i = 0; i < game->board_size; i++) {
        game->visible_board[i] = game->board[i];
    }
}

void terminate_game(game_t *game) {
    free(game->board);
    free(game);
}