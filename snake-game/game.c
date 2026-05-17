#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#include "game.h"

int game_over;
int score;

int head_x, head_y;
int food_x, food_y;

int tail_x[MAX_SANKE_LENGTH];
int tail_y[MAX_SANKE_LENGTH];
int tail_len;

Direction dir;

void setup()
{
    game_over = 0;
    score = 0;

    // make snake start in middle
    head_x = WIDTH / 2;
    head_y = HEIGHT / 2;

    // make food start in random place
    food_x = rand() % WIDTH;
    food_y = rand() % HEIGHT;

    tail_len = 0;

    dir = STOP;

    // --- 解决窗口高度问题：固定控制台缓冲区和窗口大小 ---
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // 1. 设置缓冲区大小（确保没有垂直滚动条）
    // 宽度为 WIDTH + 4（留点余量），高度为 HEIGHT + 5
    COORD bufferSize = {WIDTH + 4, HEIGHT + 5};
    SetConsoleScreenBufferSize(hOut, bufferSize);

    // 2. 设置窗口实际显示大小
    SMALL_RECT windowSize = {0, 0, WIDTH + 3, HEIGHT + 4};
    SetConsoleWindowInfo(hOut, TRUE, &windowSize);

    // 3. 隐藏光标
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut, &cci);
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cci);
}

void draw()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    SetConsoleCursorPosition(hOut, coord);

    for (int i = 0; i < WIDTH + 2; i++)
    {
        printf("#");
    }
    printf("\n");

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            // left wall
            if (x == 0)
            {
                printf("#");
            }

            // snake head
            if (x == head_x && y == head_y)
            {
                printf("O");
            }

            // food
            else if (x == food_x && y == food_y)
            {
                printf("*");
            }

            else
            {
                int print_tail = 0;
                for (int k = 0; k < tail_len; k++)
                {
                    if (tail_x[k] == x && tail_y[k] == y)
                    {
                        printf("o");
                        print_tail = 1;
                        break;
                    }
                }
                // if current position is not the head or tail
                if (!print_tail)
                {
                    printf(" ");
                }
            }

            // right wall
            if (x == WIDTH - 1)
            {
                printf("#");
            }
        }
        printf("\n");
    }

    // bottom wall
    for (int i = 0; i < WIDTH + 2; i++)
    {
        printf("#");
    }

    printf("\n");
    printf("Score: %d     \n", score);
}

void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            // 只有当当前方向不是向右时，才允许向左
            if (dir != RIGHT)
                dir = LEFT;
            break;
        case 'd':
            // 只有当当前方向不是向左时，才允许向右
            if (dir != LEFT)
                dir = RIGHT;
            break;
        case 'w':
            // 只有当当前方向不是向下时，才允许向上
            if (dir != DOWN)
                dir = UP;
            break;
        case 's':
            // 只有当当前方向不是向上时，才允许向下
            if (dir != UP)
                dir = DOWN;
            break;
        case 'x':
            game_over = 1;
            break;
        }
    }
}

void logic()
{
    if (dir == STOP)
        return;

    int prev_x = tail_x[0];
    int prev_y = tail_y[0];

    int prev2_x, prev2_y;
    tail_x[0] = head_x;
    tail_y[0] = head_y;

    for (int i = 1; i < tail_len; i++)
    {
        prev2_x = tail_x[i];
        prev2_y = tail_y[i];

        tail_x[i] = prev_x;
        tail_y[i] = prev_y;

        prev_x = prev2_x;
        prev_y = prev2_y;
    }

    switch (dir)
    {
    case LEFT:
        head_x--;
        break;
    case RIGHT:
        head_x++;
        break;
    case UP:
        head_y--;
        break;
    case DOWN:
        head_y++;
        break;
    default:
        break;
    }

    // wall collision
    if (head_x < 0 || head_x >= WIDTH || head_y < 0 || head_y >= HEIGHT)
    {
        game_over = 1;
    }

    // tail collision
    for (int i = 0; i < tail_len; i++)
    {
        if (tail_x[i] == head_x && tail_y[i] == head_y)
        {
            game_over = 1;
        }
    }

    // eat food
    if (head_x == food_x && head_y == food_y)
    {
        score += 10;
        food_x = rand() % WIDTH;
        food_y = rand() % HEIGHT;
        tail_len++;
    }
}