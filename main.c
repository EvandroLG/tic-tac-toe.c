#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    board[square] = side;
}

int getHumanMove(int *board) {
    char userInput[4];
    int moveOk = 0;
    int move = -1;

    while (moveOk == 0) {
        printf("Enter a move from 1 to 9 - ");
        fgets(userInput, 3, stdin);
        fflush(stdin);

        if (strlen(userInput) != 2) {
            printf("Invalid strlen()\n");
            continue;
        }

        if (sscanf(userInput, "%d", &move) != 1) {
            move = -1;
            printf("Invalid sscanf()\n");
            continue;
        }

        if (move < 1 || move > 9) {
            move = -1;
            printf("Invalid range\n");
            continue;
        }

        move--;

        if (board[CONVERT_TO_25[move]] != EMPTY) {
            move = -1;
            printf("Square not available\n");
            continue;
        }

        moveOk = 1;
    }

    printf("Making move...\n");
    return CONVERT_TO_25[move];
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
            getHumanMove(&board[0]);
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
