# Mines
Small project to experiment with ncurses library. The app is separated into three main modules (game, draw and controller).
1. Game
    - implementation of the game logic
2. Draw
    - Rendering to the screen
3. Controller
    - Input handling

## Build
The project can be built using the usual `make` command. And can be run with `make run`. Valgrind configuration is also provided (`make leak-check`) to check for memory leaks.

## Running the app
The app requires 3 arguments - width and height of the board to play on and number of mines to spawn.
`./main [width] [height] [mine_count]`

Where `[width]` and `[height]` must be non-zero positive integers and `[mine_count]` must be lower or equal to the total number of tiles on the board.