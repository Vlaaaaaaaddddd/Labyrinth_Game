#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "maze.h"

typedef struct {
    Point pos; //{x,y}
    int g; //Расстояние от старта
    int h; //Расстояние до финиша 
    int f; //f = g + h
} AStarNode;

int find_shortest_path(const GameState *game, Point start, Point end, Point out_path[], int *out_path_len);

#endif