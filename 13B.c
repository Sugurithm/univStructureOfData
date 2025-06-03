/*
8パズル問題
最小移動回数を求めるため，BFSを用いる．
BFSはキューを用いる（FIFO)
各状態を保存するため，ハッシュを用いて効率よく記憶する．
*/

#include <stdio.h>
#include <string.h> // memcpy
#include <stdbool.h> // bool
#include <stdlib.h> // malloc

#define N 3
#define HASH_SIZE 1000003 // 大きな素数を使用

typedef struct {
    int board[N][N];
    int moves;
    int zero_x;
    int zero_y;
} State; // 状態を格納する構造体

typedef struct Node {
    State state;
    struct Node* next;
} Node; // 各状態をキューに格納するための構造体（ノード）

typedef struct {
    Node* front;
    Node* tail;
} Queue; // キューを保存する構造体

void initQueue(Queue *q) {
    q->front = NULL;
    q->tail = NULL;
}

void enqueue(Queue *q, State state) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->state = state;
    newNode->next = NULL;

    if (q->tail == NULL) {
        q->front = newNode;
        q->tail = newNode;
    } else {
        q->tail->next = newNode;
        q->tail = newNode;
    }
}

State dequeue(Queue *q) {
    Node *temp = q->front;
    State state = temp->state;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->tail = NULL;
    }
    free(temp);
    return state;
}

// unsigned int: 符号なし整数
unsigned int getHash(int board[N][N]) {
    unsigned int hash = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            hash = hash * 31 + board[i][j]; // より良いハッシュ関数
        }
    }
    return hash % HASH_SIZE;
}

bool isGoal(int board[N][N]) {
    int goal[N][N] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] != goal[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int solve(int board[N][N]) {
    Queue q;
    initQueue(&q);

    State start;
    // memcpy( コピー元, コピー先, コピーするサイズ );
    memcpy(start.board, board, sizeof(start.board));
    start.moves = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0) {
                start.zero_x = i;
                start.zero_y = j;
                break;
            }
        }
    }

    enqueue(&q, start);
    
    // 同じ状態を何度も探索しないため，状態を保存する（ハッシュを用いる）
    bool *searched = (bool *)calloc(HASH_SIZE, sizeof(bool));
    if (!searched) return -1;
    searched[getHash(start.board)] = true;

    // 空白の移動は左右上下の4種類
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};

    // キューが空出ない間は探索（BFS）
    while (q.front != NULL) {
        State current = dequeue(&q);
        
        // 完成状態であれば終了
        if (isGoal(current.board)) {
            free(searched);
            return current.moves;
        }

        // 現在の状態から次の状態を生成
        for (int direction = 0; direction < 4; direction++) {
            // 空白（0)を動かす
            int next_x = current.zero_x + dx[direction];
            int next_y = current.zero_y + dy[direction];
            
            if (next_x >= 0 && next_x < N && next_y >= 0 && next_y < N) { // 範囲内の場合
                State next = current; // 現在の状態をコピー

                // 空白と交換
                next.board[current.zero_x][current.zero_y] = next.board[next_x][next_y];
                next.board[next_x][next_y] = 0;

                // 空白の位置を更新
                next.zero_x = next_x;
                next.zero_y = next_y;
                next.moves++;
                
                // 次の状態をキューに追加
                unsigned int hash = getHash(next.board);
                if (!searched[hash]) {
                    searched[hash] = true;
                    enqueue(&q, next);
                }
            }
        }
    }

    free(searched);
    return -1; // ゴールに到達できない場合
}

int main(void) {
    int board[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &board[i][j]);
        }
    }
    int ans = solve(board);
    printf("%d\n", ans);
    return 0;
}