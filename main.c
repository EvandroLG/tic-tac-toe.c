#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

enum { NOUGHTS, CROSSES, BORDER=3, EMPTY=0 };

const int CONVERT_TO_25[9] = {
    6, 7, 8,
    11, 12, 13,
    16, 17, 18
};

void initializeBoard(int *board) {
    for (int i = 0; i < 25; i++) {
        board[i] = BORDER;
    }

    for (int i = 0; i < 9; i++) {
        board[CONVERT_TO_25[i]] = EMPTY;
    }
}

int hasEmpty(int *board) {
    for (int i = 0; i < 9; i++) {
        if (board[CONVERT_TO_25[i]] == EMPTY) {
            return 1;
        }
    }

    return 0;
}

void makeMove(int *board, int square, int side) {

}

void printBoard(int *board) {
    char chars[] = "0X|-";

    printf("\nBoard:\n");

    for (int i = 0; i < 9; i++) {
        if (i != 0 && i % 3 == 0) {
            printf("\n");
        }

        printf("%4c", chars[board[CONVERT_TO_25[i]]]);
    }

    printf("\n");
}

void runGame() {
    int gameOver = 0;
    int side = NOUGHTS;
    int board[25];

    initializeBoard(&board[0]);
    printBoard(&board[0]);

    while (!gameOver) {
        if (side == NOUGHTS) {
        } else {
            printBoard(&board[0]);
        }
    }
}

int main() {
    /*srand(time(NULL));*/
    runGame();

    return 0;
}
