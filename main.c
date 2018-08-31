#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { NOUGHTS, CROSSES, BORDER=3, EMPTY=0 };

const int CONVERT_TO_25[9] = {
    6, 7, 8,
    11, 12, 13,
    16, 17, 18
};

const int DIRECTIONS[4] = { 1, 5, 4, 6 };

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

int getComputerMove(int *board) {
    int freeSpaces = 0;
    int randomMove = 0;
    int availableMoves[9];

    for (int i = 0; i < 9; i++) {
        if (board[CONVERT_TO_25[i]] == EMPTY) {
            availableMoves[freeSpaces++] = CONVERT_TO_25[i];
        }
    }

    randomMove = (rand() % freeSpaces);

    return availableMoves[randomMove];
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

int getNumberForDirection(int start, int direction, int *board, int us) {
    int found = 0;

    while (board[start] != BORDER) {
        if (board[start] != us) {
            break;
        }

        found++;
        start += direction;
    }

    return found;
}

int findThreeInRow(int *board, int index, int us) {
    int dir = 0;
    int threeCount = 1;

    for (int i = 0; i < 4; i++) {
        dir = DIRECTIONS[i];
        threeCount += getNumberForDirection(index + dir, dir, board, us);
        threeCount += getNumberForDirection(index + dir * -1, dir * -1, board, us);

        if (threeCount == 3) {
            break;
        }

        threeCount = 1;
    }

    return threeCount;
}

void runGame() {
    int gameOver = 0;
    int lastMoveMade = 0;
    int side = NOUGHTS;
    int board[25];

    initializeBoard(&board[0]);
    printBoard(&board[0]);

    while (!gameOver) {
        if (side == NOUGHTS) {
            lastMoveMade = getHumanMove(&board[0]);
            makeMove(&board[0], lastMoveMade, side);
            side = CROSSES;
        } else {
            lastMoveMade = getComputerMove(&board[0]);
            makeMove(&board[0], lastMoveMade, side);
            side = NOUGHTS;

            printBoard(&board[0]);
        }

        if (findThreeInRow(board, lastMoveMade, side ^ 1) == 3) {
            printf("Game over!\n");
            gameOver = 1;

            if (side == NOUGHTS) {
                printf("Computer wins\n");
            } else {
                printf("Human wins\n");
            }
        }

        if (!hasEmpty(board)) {
            printf("Game over!\n");
            gameOver = 1;
            printf("It's a draw\n");
        }
    }

    printBoard(&board[0]);
}

int main() {
    /*srand(time(NULL));*/
    runGame();

    return 0;
}
