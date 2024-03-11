#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#define ROWS 30
#define COLS 50
#define ALIVE '0'
#define DEAD '.'
#define SLEEP 250000

void print_board(char board[ROWS][COLS]);
void fill_board_random(char board[ROWS][COLS]);
int count_live_neighbour_cell(char board[ROWS][COLS], int row, int col);

int main(void)
{
    char boards[2][ROWS][COLS];
    int current_board = 0;
    int next_board = 1;

    fill_board_random(boards[0]);

    int nbors_alive;
    while (true) {
        print_board(boards[current_board]);
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                nbors_alive = count_live_neighbour_cell(boards[current_board], i, j);
                if (boards[current_board][i][j] == ALIVE && (nbors_alive == 2 || nbors_alive == 3)) {
                    boards[next_board][i][j] = ALIVE;
                } else if (boards[current_board][i][j] == DEAD && nbors_alive == 3) {
                    boards[next_board][i][j] = ALIVE;
                } else {
                    boards[next_board][i][j] = DEAD;
                }
            }
        }
        current_board = next_board;
        next_board = (next_board + 1) % 2;

        usleep(SLEEP);
    }

    return 0;
}

void print_board(char board[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++) {
        if (i > 0) {
            printf("\n");
        }

        for (int j = 0; j < COLS; j++) {
            if (j > 0) {
                printf(" ");
            }
            printf("%c", board[i][j]);
        }
    }
    printf("\n\n");
}

void fill_board_random(char board[ROWS][COLS])
{
    char options[] = {DEAD, ALIVE};
    srand(time(NULL));

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = options[rand() % 2];
        }
    }
}

int count_live_neighbour_cell(char board[ROWS][COLS], int row, int col)
{
    int count = 0;
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            if ((i == row && j == col) || (i < 0 || j < 0) || (i >= ROWS || j >= COLS)) {
                continue;
            }

            if (board[i][j] == ALIVE) {
                count++;
            }
        }
    }
    return count;
}
