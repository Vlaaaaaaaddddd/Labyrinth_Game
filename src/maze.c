#include <stdlib.h>
#include <time.h>

#include "maze.h"
#include "pathfinding.h"

void init_game_map(GameState *game) { 
    // инициализировали генератор случайных чисел
    srand(time(NULL)); 

    // Заполнили сетку (пока не будет пути перегенерируем)
    do {
        int wall_chance = 25;

        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                if (y == 0 || y == HEIGHT - 1 || x == 0 || x == WIDTH - 1) { 
                    game->grid[y][x] = CELL_WALL;
                } else { 
                    if ((rand() % 100) < wall_chance) {
                        game->grid[y][x] = CELL_WALL;
                    } else {
                        game->grid[y][x] = CELL_EMPTY;
                    }
                }
            }
        }

        // Начальные, конечные позиции 
        game->start = (Point){2, 2};
        game->end = (Point){WIDTH - 3, HEIGHT - 3};
        game->player = game->start;

        // Убираем препятствия на старте и финише
        game->grid[game->start.y][game->start.x] = CELL_START;
        game->grid[game->end.y][game->end.x] = CELL_END;
    
    } while (find_shortest_path(game, game->start, game->end, game->optimal_path, &game->optimal_path_len) == -1);

    // Начальные параметры
    game->max_cord_length = game->optimal_path_len + 5;
    game->cord_left = game->max_cord_length;

    game->game_over = false;
    game->game_won = false;
    game->path[0] = game->start; //Первая точка в истории провода 
    game->path_size = 1;
}