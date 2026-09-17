#include <ncurses.h>
#include "maze.h"
#include "display.h"

int main(void) {
    GameState game;
    
    init_display();
    init_game_map(&game);

    draw_game(&game);

    int ch;

    while ((ch = getch()) != 'q')
    {

        int next_x = game.player.x;
        int next_y = game.player.y;

        switch (ch) {
            case KEY_UP:
                next_y--;
                break;
            case KEY_DOWN:
                next_y++;
                break;
            case KEY_LEFT:
                next_x--;
                break;
            case KEY_RIGHT:
                next_x++;
                break;
        }

        if (game.grid[next_y][next_x] != CELL_WALL) {
            game.player.x = next_x;
            game.player.y = next_y;
        }

        // Отрисовка текущего состояния
        draw_game(&game);
    }

    close_display();
    return 0;   
}