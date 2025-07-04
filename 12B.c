#include <stdio.h>
#include <limits.h> // INT_MAX を使用するために必要
#include <stdbool.h> // bool 型を使用するために必要

/*
ダイクストラ法 (Dijkstra's Algorithm) の手順:
1. 開始ノードを選択し、そのコスト（距離）を0とする。他の全てのノードのコストは無限大に設定する。
2. 未訪問のノードの中から、現在コスト（距離）が最小のノードを選び出す。
3. 選んだノードを訪問済みとしてマークする。
4. 選んだノードから到達可能な全ての隣接ノードについて、現在の最短経路を更新できるか確認する。
　　もし新しい経路の方が短い場合、その隣接ノードのコストを更新する。
5. 全てのノードの最短距離が確定するか、これ以上到達可能なノードがない場合、処理を終了する。
*/

void dijkstra(int n, int adj_matrix[n][n], int ans_distance[n]) {
    int distance[n]; 
    bool visited[n]; 

    for (int i = 0; i < n; i++) {
        distance[i] = INT_MAX; 
        visited[i] = false; 
    }
    distance[0] = 0;

    for (int count = 0; count < n; count++) {
        int u = -1; 
        int min_dist = INT_MAX; 

        for (int v = 0; v < n; v++) {
            if (!visited[v] && distance[v] < min_dist) {
                min_dist = distance[v];
                u = v;
            }
        }

        if (u == -1) break;

        visited[u] = true;
        ans_distance[u] = distance[u];
        
        for (int v = 0; v < n; v++) {
            if (!visited[v] && adj_matrix[u][v] != INT_MAX && distance[u] != INT_MAX &&
                distance[u] + adj_matrix[u][v] < distance[v]) {
                distance[v] = distance[u] + adj_matrix[u][v];
            }
        }
    }
}

int main(void) {
    int n;
    scanf("%d", &n);
    
    int adj_matrix[n][n];
    int ans_distance[n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj_matrix[i][j] = INT_MAX;
            // if (i == j) adj_matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        int u_node, k_out_degree;
        scanf("%d %d", &u_node, &k_out_degree);
        for (int j = 0; j < k_out_degree; j++) {
            int v_adjacent, c_cost;
            scanf("%d %d", &v_adjacent, &c_cost);
            adj_matrix[u_node][v_adjacent] = c_cost;
        }
    }

    dijkstra(n, adj_matrix, ans_distance);

    for (int i = 0; i < n; i++) {
        printf("%d %d\n", i, ans_distance[i]);
    }

    return 0;
}