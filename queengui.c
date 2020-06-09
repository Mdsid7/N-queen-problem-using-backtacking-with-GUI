#define N 8

#define COLOR_BGW   "\x1b[47m"
#define COLOR_BGB   "\x1b[100m"
#define COLOR_BLK   "\x1b[30m"
#define COLOR_RESET "\x1b[0m"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum {false,true} bool;

void continuee() {
    printf("\n Press [Enter] for another solution.");
    while (getchar() !='\n');
}

void wait(unsigned int secs) {              // Wait x seconds
    unsigned int retTime = time(0) + secs;  // Get finishing time.
    while (time(0) < retTime);              // Loop until it arrives.
}

int color(int i, int j) {
    return (i+j)%2;
}

int countSLT() {
    static int k = 0;
    return k++;
}
 
void printBoard(int board[N][N], int delay) {
    system("clear");
    int i,j;
    if (delay) printf("\n N-QUEENS (delay=1s)\n\n");
    else printf("\n N-QUEENS\n\n");
    for (i=0; i<N; i++) {
        printf(" %d ", i+1);
        for (j=0; j<N; j++)
            if (!color(i,j)) {
                if (board[i][j])
                    printf(COLOR_BGW COLOR_BLK " \u265B " COLOR_RESET);
                else
                    printf(COLOR_BGW "   " COLOR_RESET);
            }
            else {
                if (board[i][j])
                    printf(COLOR_BGB COLOR_BLK " \u265B " COLOR_RESET);
                else
                    printf(COLOR_BGB "   " COLOR_RESET);
            }
        printf("\n");
    }
    printf("   ");
    for (i=0; i<N; i++) {
        printf(" %c ", i+97);
    }
    if (delay) printf("\n\n Processing...\n (ctrl+c to abort)\n");
    else printf("\n");
}

bool valida(int board[N][N], int row, int col) {
    int i,j;

    for (i=0; i<col; i++)
        if (board[row][i])
            return false;
 
    for (i=row,j=col; i>=0 && j>=0; i--,j--)
        if (board[i][j])
            return false;
 
    for (i=row, j=col; j>=0 && i<N; i++,j--)
        if (board[i][j])
            return false;

    return true;
}
 
 /*bool solve(int board[N][N], int col) {
    int i;
    if (col>=N) return true;
    for (i=0; i<N; i++) {
        if (valida(board,i,col)) {
            board[i][col] = 1; 
            if (solve(board,col+1))
                return true;
            board[i][col] = 0;
        }
    }
    return false;
} */

bool solve(int board[N][N], int col, int delay) {
    int i;
    bool solution = false;
    
    if (col == N) {
        printBoard(board,delay);
        printf("\n Solucao: %d", countSLT());
        continuee();
        return true;
    }
    
    for (i=0; i<N; i++) {
        if (valida(board,i,col)) {
            board[i][col] = 1;
            printBoard(board,delay);
            if (delay) wait(1);
            solution= solve(board,col+1,delay) || solution;
            board[i][col] = 0;
            printBoard(board,delay);
            if (delay) wait(1);
        }
    }
    return solution;
}
 
void callNQ() {
    system("clear");
    int board[N][N];
    bool delay = false;
    char ask;
    memset(board,0,sizeof(board));
    printf("\n Use the delay to visualize the backtracking? [y/n]");
    ask = getchar();
    if (ask == 'y') delay = true;
    if (!solve(board,0,delay)) {
        printf("There is no solution\n");
        return;
    }
    return;
}
 
int main(void) {
    callNQ();
    return 0;
}
