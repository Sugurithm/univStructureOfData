#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

#define INFTY 2000000000

// 荷物の重さと元のインデックスを保持する構造体
typedef struct {
    int weight;
    int original_index;
} Item;

int compareItems(const void *a, const void *b) {
    return ((Item *)a)->weight - ((Item *)b)->weight;
}

long long minCostSort(int w[], int n) {
    Item *original_items = (Item *)malloc(sizeof(Item) * n);
    Item *sorted_items = (Item *)malloc(sizeof(Item) * n);

    int max_weight_val = 0;

    // original_items と sorted_items を初期化
    for (int i = 0; i < n; i++) {
        original_items[i].weight = w[i];
        original_items[i].original_index = i;

        sorted_items[i].weight = w[i];
        sorted_items[i].original_index = i;

        if (w[i] > max_weight_val) {
            max_weight_val = w[i];
        }
    }
    qsort(sorted_items, n, sizeof(Item), compareItems); // 重さの小さい順にソート

    long long min_global_weight = sorted_items[0].weight; // 全体の中で重さが最小の荷物の重さ

    // 各重さの値がソートされたときに，どのインデックスになるべきかを記録するマップ
    int *val_to_target_idx = (int *)malloc(sizeof(int) * (max_weight_val + 1));
    for (int i = 0; i < n; i++) {
        val_to_target_idx[sorted_items[i].weight] = i; // sorted_items[i].weight の値はソート後のインデックス i に対応
    }

    // 各荷物が既に処理済みかどうかを記録する配列
    bool *visited = (bool *)calloc(n, sizeof(bool));

    long long total_min_cost = 0; // 全体の最小コストの合計

    // 各荷物をループしてサイクルを見つけ，コストを計算
    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        
        // original_items[i] の重さが，ソートされた時の i 番目の重さと同じなら，すでに正しい位置
        if (original_items[i].weight == sorted_items[i].weight) {
            visited[i] = true; // 訪問済みにする
            continue;          // 次の荷物へ
        }

        long long current_cycle_sum = 0;    // 今見ているサイクルの重さの合計
        int min_weight_in_cycle = INFTY;    // 今見ているサイクルの最小重さ
        int cycle_length = 0;               // 今見ているサイクルの長さ

        int current_original_index = i; // 現在注目している original_items のインデックス

        // サイクルをたどるループ
        while (!visited[current_original_index]) {
            visited[current_original_index] = true; // 現在の荷物を訪問済みにする
            
            int current_weight_val = original_items[current_original_index].weight;
            current_cycle_sum += current_weight_val; // 重さを合計に加える

            if (current_weight_val < min_weight_in_cycle) {
                min_weight_in_cycle = current_weight_val; // サイクルの最小重さを更新
            }
            cycle_length++; // サイクルの長さを増やす

            // 次にサイクルをたどる荷物のインデックスを求める
            // その「来るべきインデックス」に現在いる荷物が，サイクルの次の要素になる
            current_original_index = val_to_target_idx[current_weight_val];
        }

        long long cost_option1 = current_cycle_sum + (long long)(cycle_length - 2) * min_weight_in_cycle;
        long long cost_option2 = current_cycle_sum + min_weight_in_cycle + (long long)(cycle_length + 1) * min_global_weight;
        
        if ( cost_option1 < cost_option2 ) {
            total_min_cost += cost_option1;
        } else {
            total_min_cost += cost_option2;
        }
    }

    // メモリ解放
    free(original_items);
    original_items = NULL;
    free(sorted_items);
    sorted_items = NULL;
    free(val_to_target_idx);
    val_to_target_idx = NULL;
    free(visited);
    visited = NULL;

    return total_min_cost;
}

int main(void){
    int n;
    scanf("%d", &n);

    int *w = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++){
        scanf("%d", &w[i]);
    }

    long long result = minCostSort(w, n);
    printf("%lld\n", result);

    free(w);
    w = NULL;

    return 0;
}