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
        switch (ch) 
        {
            case KEY_UP:
                game.player.y--; // Двигаем вверх
                break;
            case KEY_DOWN:
                game.player.y++; // Двигаем вниз
                break;
            case KEY_LEFT:
                game.player.x--; // Двигаем влево
                break;
            case KEY_RIGHT:
                game.player.x++; // Двигаем вправо
                break;
        }

        // Отрисовка текущего состояния
        draw_game(&game);
    }

    close_display();
    return 0;   
}