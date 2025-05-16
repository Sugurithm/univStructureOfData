#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value; // 値
    int outdeg; // 出次数
    int *vertex; // 隣接頂点のリスト
} Node;

Node* nodes;
int distance[101]; // 距離
int queue[101]; // これから訪問予定であるノード
int head = 0; // queueの先頭
int tail = 0; // queueの末尾

void enqueue(int v) {
    queue[tail] = v;
    tail++;
}

int dequeue() {
    int v = queue[head];
    head++;
    return v;
}

/*
幅優先探索
計算量：O(V + E)
V: 頂点数
E: 辺の数
*/
void bfs(int start) {
    // 初期化
    for (int i = 0; i < 101; i++) {
        distance[i] = -1;
    }

    distance[start] = 0;
    // 初めの頂点をqueueに追加
    enqueue(start);

    // queueが空になるまで探索を続ける
    while (head < tail) {
        int u = dequeue(); // queueの先頭を取り出す
        // uの隣接頂点を訪問
        // 未訪問であれば，距離を更新し，queueに追加
        for (int i = 0; i < nodes[u].outdeg; i++) {
            int v = nodes[u].vertex[i];
            if (distance[v] == -1) {
                distance[v] = distance[u] + 1;
                enqueue(v);
            }
        }
    }
}

int main() {
    // input
    int n;
    scanf("%d", &n);

    nodes = (Node*)malloc((n + 1) * sizeof(Node));
    for (int i = 0; i < n; i++) {
        int id, k;
        scanf("%d %d", &id, &k);
        nodes[id].value = id;
        nodes[id].outdeg = k;
        nodes[id].vertex = (int*)malloc(k * sizeof(int));
        for (int j = 0; j < k; j++) {
            scanf("%d", &nodes[id].vertex[j]);
        }
    }

    // BFSの実行
    bfs(1);

    // output
    for (int i = 1; i <= n; i++) {
        printf("%d %d\n", i, distance[i]);
    }

    // メモリの解放
    for (int i = 1; i <= n; i++) {
        free(nodes[i].vertex);
    }
    free(nodes);
    nodes = NULL;

    return 0;
}