#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value; // 値
    int outdeg; // 出次数
    int *vertex; // 隣接頂点のリスト
} Node;

Node* nodes;
// 1 <= n <= 100 のため，0...100までの配列を用意
int d[101] = {0}; // はじめに発見した時刻
int f[101] = {0}; // 隣接リストを調べ終えた時刻
int visited[100] = {0};
int time = 1;

/*
深さ優先探索
計算量：O(V + E)
V: 頂点数
E: 辺の数
*/
void dfs(int u){
    // ノードuを最初に訪問した時刻
    d[u] = time++; 

    // ノードuの隣接ノードを訪問
    for (int i = 0; i < nodes[u].outdeg; i++) {
        int v = nodes[u].vertex[i];

        // ノードvが未訪問の場合，dfsを再帰的に呼び出す
        if (!visited[v]) {
            visited[v] = 1;
            dfs(v);
        }
    }

    // ノードuの隣接ノードをすべて訪問した後，ノードuを訪問した時刻
    f[u] = time++;
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
    

    // DFSの実行
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            visited[i] = 1;
            dfs(i);
        }
    }

    // output
    for (int i = 1; i <= n; i++) {
        printf("%d %d %d\n", nodes[i].value, d[i], f[i]);
    }

    // メモリ解放
    for (int i = 1; i <= n; i++) {
        free(nodes[i].vertex);
    }
    free(nodes);
    nodes = NULL;

    return 0;
}