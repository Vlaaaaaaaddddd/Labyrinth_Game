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
        if (game.game_over || game.game_won) {
            continue;
        }

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

        if (game.grid[next_y][next_x] == CELL_END) {
            game.game_won = true;
        }

        if ((next_x != game.player.x || next_y != game.player.y) 
             && game.grid[next_y][next_x] != CELL_WALL) {
            if (game.path_size > 1 &&
                next_x == game.path[game.path_size - 2].x && 
                next_y == game.path[game.path_size - 2].y) {
                    if (game.grid[game.player.y][game.player.x] == CELL_CORD) {
                        game.grid[game.player.y][game.player.x] = CELL_EMPTY;
                    }
                    game.path_size--;
                    game.cord_left++;
                    game.player.x = next_x;
                    game.player.y = next_y;
                }

            else if (game.cord_left > 0) {
                if (game.grid[next_y][next_x] == CELL_EMPTY) {
                    game.grid[next_y][next_x] = CELL_CORD;
                }
                
                game.player.x = next_x;
                game.player.y = next_y;
                
                game.path[game.path_size] = (Point){next_x, next_y};
                game.path_size++;
                game.cord_left--;
            }
    }

    if (game.cord_left <= 0 && !game.game_won){
                game.game_over = true;
    }       
        // Отрисовка текущего состояния
        draw_game(&game);
    }

    close_display();
    return 0;   
}