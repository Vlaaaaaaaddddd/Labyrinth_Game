#include <ncurses.h>

int main(void) {
    initscr(); //режим терминала 
    cbreak(); //символы читаются сразу 
    noecho(); //не отображать клавиши 
    keypad(stdscr, TRUE); //включаем стрелки 
    curs_set(0); //прячем курсор 
    
    // Задаем стартовую позицию игрока 
    int player_x = 0;
    int player_y = 5;

    int ch;
    // Игровой цикл выход на q
    while ((ch = getch()) != 'q')
    {
        clear();

        mvprintw(0, 0, "Press 'q' to exit.");
        mvprintw(1, 0, "Use ARROW KEYS to move.");

        switch (ch) 
        {
            case KEY_UP:
                player_y--; // Двигаем вверх (уменьшаем Y)
                break;
            case KEY_DOWN:
                player_y++; // Двигаем вниз (увеличиваем Y)
                break;
            case KEY_LEFT:
                player_x--; // Двигаем влево
                break;
            case KEY_RIGHT:
                player_x++; // Двигаем вправо
                break;
        }
        mvaddch(player_y, player_x, '@');

        refresh();
    }

endwin();
return 0;   
}