// 8 queen problem

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define SQUARE_COUNT 8

int board[SQUARE_COUNT][SQUARE_COUNT];
int found = FALSE; // 解を見つけたかどうか

void initialize(int board[SQUARE_COUNT][SQUARE_COUNT]){
    for (int i = 0; i < SQUARE_COUNT; i++){
        for (int j = 0; j < SQUARE_COUNT; j++){
            board[i][j] = FALSE;
        }
    }
}

int duplication(int x, int y){
    for (int i = 0; i < SQUARE_COUNT; i++){
        if (board[x][i] == TRUE || board[i][y] == TRUE){
            return TRUE;
        }
    }

    for (int i = 0; i < SQUARE_COUNT; i++){
        for (int j = 0; j < SQUARE_COUNT; j++){
            if (abs(i - x) == abs(j - y) && board[i][j] == TRUE){
                return TRUE;
            }
        }
    }
    return FALSE;
}

void showBoard(int board[SQUARE_COUNT][SQUARE_COUNT]){
    for (int i = 0; i < SQUARE_COUNT; i++){
        for (int j = 0; j < SQUARE_COUNT; j++){
            if (board[i][j] == TRUE){
                printf("Q");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}

int countQueens(){
    int count = 0;
    for (int i = 0; i < SQUARE_COUNT; i++){
        for (int j = 0; j < SQUARE_COUNT; j++){
            if (board[i][j] == TRUE){
                count++;
            }
        }
    }
    return count;
}

// 指定した列にクイーンがあるか
int hasQueen(int x){
    for (int i = 0; i < SQUARE_COUNT; i++){
        if (board[x][i] == TRUE){
            return TRUE;
        }
    }
    return FALSE;
}

// DFSの原理で解を探索する．
void solveQueen(int x){
    if (found) return; // 既に解を見つけていたら再帰関数から抜ける

    // 指定した列にクイーンがあれば，次の列を探索
    if (hasQueen(x)){
        solveQueen(x + 1);
        return;
    }

    // 指定した列にクイーンがない場合，その列にクイーンを置く．
    // 置いた場合を探索し，解を見つけれなかった場合は，元に戻る（DFS）
    for (int y = 0; y < SQUARE_COUNT; y++){
        if (!duplication(x, y)){
            board[x][y] = TRUE;
            solveQueen(x + 1);

            if (found) return;
    
            board[x][y] = FALSE;
        }
    }

    // 解を見つけたら終了（フラグをTRUEにする）
    if (countQueens() == SQUARE_COUNT){
        found = TRUE;
        return;
    }
}

int main(void){

    initialize(board);

    // 入力
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        board[x][y] = TRUE;
    }

    // 処理
    solveQueen(0);

    // 出力
    showBoard(board);

    return 0;
}