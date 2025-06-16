#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>

#define EMPTY 0
#define WALL 1
#define BODY 2
#define FOOD 3
#define WIDTH 30
#define HEIGHT 30
#define DELAY 150000

typedef int POSITION;

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point body[WIDTH * HEIGHT];
    int length;
    int direction;
} Snake;

int map[HEIGHT][WIDTH];
Snake snake;
Point food;

void initScreen() {
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(DELAY / 1000);
}

void initGame() {
    // 初始化地图
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
                map[i][j] = WALL;
            else
                map[i][j] = EMPTY;
        }
    }
    
    // 初始化蛇
    snake.length = 3;
    snake.direction = 1; // 右
    for (int i = 0; i < snake.length; i++) {
        snake.body[i].x = WIDTH / 2 - i;
        snake.body[i].y = HEIGHT / 2;
        map[snake.body[i].y][snake.body[i].x] = BODY;
    }
    
    // 生成食物
    srand(time(NULL));
    do {
        food.x = rand() % (WIDTH - 2) + 1;
        food.y = rand() % (HEIGHT - 2) + 1;
    } while (map[food.y][food.x] != EMPTY);
    map[food.y][food.x] = FOOD;
}

void drawGame() {
    clear();
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            switch (map[i][j]) {
                case WALL: mvprintw(i, j, "#"); break;
                case BODY: mvprintw(i, j, "O"); break;
                case FOOD: mvprintw(i, j, "*"); break;
                default: mvprintw(i, j, " "); break;
            }
        }
    }
    refresh();
}

void moveSnake() {
    Point next = snake.body[0];
    switch (snake.direction) {
        case 0: next.y--; break;
        case 1: next.x++; break;
        case 2: next.y++; break;
        case 3: next.x--; break;
    }
    
    if (map[next.y][next.x] == WALL || map[next.y][next.x] == BODY) {
        endwin();
        printf("Game Over!\n");
        exit(0);
    }
    
    if (map[next.y][next.x] == FOOD) {
        snake.length++;
        do {
            food.x = rand() % (WIDTH - 2) + 1;
            food.y = rand() % (HEIGHT - 2) + 1;
        } while (map[food.y][food.x] != EMPTY);
        map[food.y][food.x] = FOOD;
    } else {
        Point tail = snake.body[snake.length - 1];
        map[tail.y][tail.x] = EMPTY;
    }
    
    for (int i = snake.length - 1; i > 0; i--) {
        snake.body[i] = snake.body[i - 1];
    }
    
    snake.body[0] = next;
    map[next.y][next.x] = BODY;
}

void handleInput() {
    int ch = getch();
    switch (ch) {
        case KEY_UP: if (snake.direction != 2) snake.direction = 0; break;
        case KEY_RIGHT: if (snake.direction != 3) snake.direction = 1; break;
        case KEY_DOWN: if (snake.direction != 0) snake.direction = 2; break;
        case KEY_LEFT: if (snake.direction != 1) snake.direction = 3; break;
        case 'q': endwin(); exit(0);
    }
}

int main() {
    initScreen();
    initGame();
    while (1) {
        handleInput();
        moveSnake();
        drawGame();
        usleep(DELAY);
    }
    endwin();
    return 0;
}
