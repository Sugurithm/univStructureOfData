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

// 各頂点（ノード）の番号と、始点からの最短距離を出力する関数
void dijkstra(int n, int adj_matrix[n][n], int ans_distance[n]) {
    int distance[n]; // 始点からの最短距離を保持する配列
    bool visited[n]; // 各ノードが訪問済みかどうかを保持する配列

    // 1. 全てのノードの距離を無限大に設定し、未訪問にする。始点（ノード0）の距離は0。
    for (int i = 0; i < n; i++) {
        distance[i] = INT_MAX; // 全ての距離を無限大（非常に大きな値）で初期化
        visited[i] = false;    // 全てのノードを未訪問にマーク
    }
    distance[0] = 0; // 始点（ノード0）からノード0への距離は0

    // n回繰り返す（最大でn個のノードを訪問する）
    for (int count = 0; count < n; count++) {
        // 2. 未訪問のノードの中から、現在コスト（距離）が最小のノードを選び出す。
        int u = -1; // 今回選択するノードのインデックス。-1は未選択を示すのがよりロバスト。
        int min_dist = INT_MAX; // 現時点での最小距離

        for (int v = 0; v < n; v++) {
            // ノードvが未訪問であり、かつ、vへの距離が現在の最小距離より小さい場合
            if (!visited[v] && distance[v] < min_dist) {
                min_dist = distance[v]; // 最小距離を更新
                u = v; // 選択するノードをvに設定
            }
        }

        // もし、到達可能な未訪問ノードがもうなければ、ループを終了する
        // （「0 から各ノードへは必ず経路が存在する」という制約があるので、通常はn回全て実行されるはず）
        if (u == -1) {
            break;
        }

        // 3. 選んだノードを訪問済みとしてマークする。
        visited[u] = true;
        
        // 問題の出力形式に従い、選ばれたノードとその最短距離を出力
        ans_distance[u] = distance[u];

        // 4. 選んだノード (u) から到達可能な全ての隣接ノード (v) について、最短経路を更新できるか確認する。
        for (int v = 0; v < n; v++) {
            // vが未訪問であり、uからvへの辺が存在し (adj_matrix[u][v]がINT_MAXでない)、
            // uへの距離が無限大でなく（INT_MAXからの加算はオーバーフローの可能性があるため）、
            // かつ「uを経由する経路（distance[u] + adj_matrix[u][v]）」が「vへの現在の最短距離（distance[v]）」より短い場合
            if (!visited[v] && adj_matrix[u][v] != INT_MAX && distance[u] != INT_MAX &&
                distance[u] + adj_matrix[u][v] < distance[v]) {
                distance[v] = distance[u] + adj_matrix[u][v]; // vの最短距離を更新
            }
        }
    }
}

int main(void) {
    int n;
    scanf("%d", &n); // グラフの頂点数nを読み込む
    
    // n x n の隣接行列を宣言
    int adj_matrix[n][n];
    int ans_distance[n];

    // 隣接行列を全てINT_MAX（辺がない状態）で初期化
    // 有向グラフなので、自己ループのコストを0に設定する必要はありません。
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj_matrix[i][j] = INT_MAX;
            // ★以前の修正で指摘したこの行は削除してください。
            // if (i == j) adj_matrix[i][j] = 0;
        }
    }

    // 各頂点の隣接リストを読み込み、隣接行列に設定する
    for (int i = 0; i < n; i++) {
        int u_node, k_out_degree; // u と k を明示的に読み込むための変数
        scanf("%d %d", &u_node, &k_out_degree); // 頂点uと、その出次数kを読み込む
        for (int j = 0; j < k_out_degree; j++) {
            int v_adjacent, c_cost;
            scanf("%d %d", &v_adjacent, &c_cost); // uに隣接する頂点vと、uからvへの辺の重みcを読み込む
            adj_matrix[u_node][v_adjacent] = c_cost; // 隣接行列に重みを設定
        }
    }

    // ダイクストラ法を実行し、結果を出力
    dijkstra(n, adj_matrix, ans_distance);

    for (int i = 0; i < n; i++) {
        printf("%d %d\n", i, ans_distance[i]);
    }

    return 0; // プログラムを正常終了
}