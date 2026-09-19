#include <ncurses.h>
#include "display.h"

void init_display(void){ 
    // Настройки ncurses
    initscr(); //режим терминала 
    cbreak(); //символы читаются сразу 
    noecho(); //не отображать клавиши 
    keypad(stdscr, TRUE); //включаем стрелки 
    curs_set(0); //прячем курсор 

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_BLUE, COLOR_BLACK);   // Стены
        init_pair(2, COLOR_GREEN, COLOR_BLACK);  // Старт
        init_pair(3, COLOR_RED, COLOR_BLACK);    // Финиш
        init_pair(4, COLOR_YELLOW, COLOR_BLACK); // Игрок / провод
        init_pair(5, COLOR_CYAN, COLOR_BLACK);   // Оптимальный путь
    }
}

void draw_game(const GameState *game){
    attrset(A_NORMAL); //сброс атрибутов
    bkgd(COLOR_PAIR(0));
    clear();

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            CellType cell = game->grid[y][x];

            switch (cell) {
                case CELL_WALL:
                    attron(COLOR_PAIR(1));
                    mvaddch(y, x, '#');
                    attroff(COLOR_PAIR(1));
                    break;

                case CELL_START:
                    attron(COLOR_PAIR(2));
                    mvaddch(y, x, 'S');
                    attroff(COLOR_PAIR(2));
                    break;

                case CELL_END:
                    attron(COLOR_PAIR(3));
                    mvaddch(y, x, 'E');
                    attroff(COLOR_PAIR(3));
                    break;

                case CELL_CORD:
                    attron(COLOR_PAIR(4));
                    mvaddch(y, x, '*');
                    attroff(COLOR_PAIR(4));
                    break;

                case CELL_EMPTY:
                default:
                    mvaddch(y, x, ' '); // Пустые клетки зарисовываем пробелом
                    break;
            }
        }
    }

    // Игрок поверх карты 
    attron(COLOR_PAIR(4));
    mvaddch(game->player.y, game->player.x, '@');
    attroff(COLOR_PAIR(4));

    // Худ
    attrset(A_NORMAL);
    mvprintw(HEIGHT + 1, 0, "Cord left: %d/%d", game->cord_left, game->max_cord_length);
    mvprintw(HEIGHT + 2, 0, "Press 'q' to quit.");

    if (game->game_won) {
        attron(COLOR_PAIR(2));
        mvprintw(HEIGHT + 4, 0, "YOU WIN! Power connected!");
        attroff(COLOR_PAIR(2));
    } else if (game->game_over) {
        attron(COLOR_PAIR(3));
        mvprintw(HEIGHT + 4, 0, "GAME OVER! Out of cord!");
        attroff(COLOR_PAIR(3));

        attron(COLOR_PAIR(5)); 
        for (int i = 0; i < game->optimal_path_len; i++) {
            Point pt = game->optimal_path[i];
            
            // Не зарисовываем старт и финиш
            if ((pt.x == game->start.x && pt.y == game->start.y) ||
                (pt.x == game->end.x && pt.y == game->end.y)) {
                continue;
            }

            mvaddch(pt.y, pt.x, '.');
        }
        attroff(COLOR_PAIR(5));
    }

    refresh();
}

void close_display(void){
    endwin();   
}