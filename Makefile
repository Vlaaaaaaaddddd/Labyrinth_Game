CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LIBS = -lncurses

SRC = src/main.c src/maze.c src/display.c src/pathfinding.c
TARGET = maze_game

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)

.PHONY: all clean