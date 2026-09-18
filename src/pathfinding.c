#include <stdlib.h>
#include <stdbool.h>
#include "pathfinding.h"

typedef struct {
    Point pos;
    int f;
} HeapNode;

typedef struct {
    HeapNode nodes[WIDTH * HEIGHT];
    int size;
} MinHeap;

// Вставка в кучу
static void heap_push(MinHeap *heap, Point pos, int f) {
    int i = heap->size++;
    heap->nodes[i] = (HeapNode){pos, f};

    // Просеивание вверх 
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap->nodes[parent].f <= heap->nodes[i].f){
             break;
        }

        // Меняем местами с родителем, если родитель больше
        HeapNode temp = heap->nodes[i];
        heap->nodes[i] = heap->nodes[parent];
        heap->nodes[parent] = temp;

        i = parent;
    }
}

// Извлечение из кучи
static HeapNode heap_pop(MinHeap *heap) {
    HeapNode min_node = heap->nodes[0];
    heap->nodes[0] = heap->nodes[--heap->size];

    int i = 0;
    // Просеивание вниз
    while (2 * i + 1 < heap->size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = left;

        if (right < heap->size && heap->nodes[right].f < heap->nodes[left].f) {
            smallest = right;
        }

        if (heap->nodes[i].f <= heap->nodes[smallest].f) break;

        HeapNode temp = heap->nodes[i];
        heap->nodes[i] = heap->nodes[smallest];
        heap->nodes[smallest] = temp;

        i = smallest;
    }

    return min_node;
}

static int heuristic(Point a, Point b) { 
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int find_shortest_path(const GameState *game, Point start, Point end){
    int g_score[HEIGHT][WIDTH]; 
    bool closed_set[HEIGHT][WIDTH];

    for (int i = 0; i < HEIGHT; i++){ 
        for (int j = 0; j < WIDTH; j++){
            g_score[i][j] = 9999;
            closed_set[y][x] = false;
        }
    }
    g_score[start.y][start.x] = 0;
    
    MinHeap open_set = { .size = 0 };
    int start_f = heuristic(start, end);
    heap_push(&open_set, start, start_f);

    while (open_set.size > 0) {
        //достали узел с минимальным f
        HeapNode current_node = heap_pop(&open_set); 
        Point current = current_node.pos;

        //пропускаем, если точка уже обрабатывалась
        if (closed_set[current.y][current.x]){
            continue;
        } 

        //если точка финиш
        if (current.x == end.x && current.y == end.y) {
            return g_score[current.y][current.x];
        }

        // Помечаем точку как посещенную
        closed_set[current.y][current.x] = true;

        // Проходимся по соседям
        static const Point dirs[4] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

        for (int i = 0; i < 4; i++) {
            Point neighbor = {current.x + dirs[i].x, current.y + dirs[i].y};
            // Проверка границ карты
            if (neighbor.x < 0 || neighbor.x >= WIDTH || neighbor.y < 0 || neighbor.y >= HEIGHT) {
                continue;
            }

            // Проверка на стену (предполагаем, что WALL = 1)
            if (game->grid[neighbor.y][neighbor.x] == CELL_WALL) {
                continue;
            }

            // Если сосед уже посещен
            if (closed_set[neighbor.y][neighbor.x]) {
                continue;
            }

            // Новое расстояние до соседа
            int tentative_g = g_score[current.y][current.x] + 1;

            if (tentative_g < g_score[neighbor.y][neighbor.x]) {
                g_score[neighbor.y][neighbor.x] = tentative_g;
                int f_score = tentative_g + heuristic(neighbor, end);
                heap_push(&open_set, neighbor, f_score);
            }
    }

    return -1;
}
