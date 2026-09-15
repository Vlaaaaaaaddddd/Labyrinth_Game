#ifndef MAZE_H
#define MAZE_H

#include <stdbool.h>

// Размеры поля
#define WIDTH 16
#define HEIGHT 16

// Типы клеток
typedef enum {
    CELL_EMPTY,
    CELL_WALL,
    CELL_START,
    CELL_END,
    CELL_CORD,
    CELL_PATH
} CellType;

// Хранение координат
typedef struct {
    int x;
    int y;
} Point;

// Состояние игры 
typedef struct {
    CellType grid[HEIGHT][WIDTH];
    Point start;
    Point end;
    Point player;
    int max_cord_length; //максимальная длина провода 
    int cord_left; //остаток провода
    bool game_over;
    bool game_won;
} GameState;

// Прототип функции (просто обещание, что функция такая существует)
void init_game_map(GameState *game);

#endif