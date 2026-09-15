#ifndef DISPLAY_H
#define DISPLAY_H

#include "maze.h"

void init_display(void);
void draw_game(const GameState *game);
void close_display(void);

#endif