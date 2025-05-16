#include <stdio.h>

int isOK(int A[],int n, int k, int maxWeight) {
    int truckCount = 1;
    int currentWeight = 0;

    for (int i = 0; i < n; i++) {

        // 荷物A[i]が最大重量を超える場合
        if (A[i] > maxWeight) return 0;

        // 荷物A[i]を積むときに最大重量を超えない場合
        if (currentWeight + A[i] <= maxWeight) {
            currentWeight += A[i];
        // 超える場合，次のトラックへ
        } else {
            currentWeight = A[i];
            truckCount++;
        }
    }
    return truckCount <= k;
}

int main() {
    // 入力
    int n, k;
    scanf("%d %d", &n, &k);
    int w[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
    }
    

    // 処理
    int ok = 0, ng = 1000000000;
    // 最小となる積載量を二分探索で
    while (ok + 1 < ng) {
        int mid = (ok + ng) / 2;
        if (isOK(w, n, k, mid)) {
            ng = mid;
        } else {
            ok = mid;
        }
    }

    // 出力
    printf("%d\n", ng);
    return 0;
}