// 最小全域木(MST) の総錘
/*
プリムのアルゴリズムを用いる．
１．任意の頂点から始める．
２．MSTの頂点群と，MSTではない頂点群を繋ぐ辺を繋ぐときの最小のコストを見つける．
３．その辺を繋びる.
*/

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

int findMinCost(int n, int min_cost[], bool visited[]) {
    int min_index = -1;
    for (int i = 0; i < n; i++) { // 連結先の頂点を探す
        if (visited[i]) continue; // 既に訪問済みであればスキップ
        if (min_index == -1 || min_cost[i] < min_cost[min_index])  {
            min_index = i;
        }
    }
    return min_index;
}

int calculateMinWeight(int n, int adj_matrix[n][n]) {
    int min_cost[n];
    bool visited[n];

    // 初期化
    for (int i = 0; i < n; i++) {
        min_cost[i] = INT_MAX;
        visited[i] = false;
    }

    min_cost[0] = 0; // 任意の頂点からスタート

    int total_cost = 0;
    for (int i = 0; i < n; i++) {
        int min_index = findMinCost(n, min_cost, visited); // 最小コストの辺を探す
        if (min_index == -1) break;
    
        visited[min_index] = true;
        total_cost += min_cost[min_index];

        for (int j = 0; j < n; j++) {
            if (!visited[j] && adj_matrix[min_index][j] == -1) continue; // 訪問済み or 自分自身
            if (min_cost[j] > adj_matrix[min_index][j]) { // 最小コストの辺を更新
                min_cost[j] = adj_matrix[min_index][j];
            }
        }
    }

    return total_cost;
}

int main(void) {
    int n;
    scanf("%d", &n);

    int adj_matrix[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &adj_matrix[i][j]);
        }
    }

    int ans = calculateMinWeight(n, adj_matrix);
    printf("%d\n", ans);
    return 0;
}