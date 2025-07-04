#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// 2つの値のうち小さい方を返すマクロ
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main() {
    int n;
    scanf("%d", &n);

    int p[n + 1]; 
    int r, c;

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &r, &c);
        p[i] = r;
        p[i + 1] = c;
    }

    // DPテーブルの定義
    // dp[i][j]: 連鎖の開始行列を i と終了行列を j とする場合の最小コスト
    long long dp[n + 1][n + 1]; 
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                dp[i][j] = 0; // 同一行列の場合はコストは0
            } else {
                dp[i][j] = LLONG_MAX;
            }
        }
    }

    // DP計算
    for (int len = 2; len <= n; len++) {
        // i: 連鎖の開始行列のインデックス (1から n - len + 1 まで)
        for (int i = 1; i <= n - len + 1; i++) {
            // j: 連鎖の終了行列のインデックス (i + len - 1)
            int j = i + len - 1;

            // k: 分割点 (iから j-1 まで)
            for (int k = i; k < j; k++) {
                // M_i ... M_k の次元は p[i-1] x p[k]
                // M_{k+1} ... M_j の次元は p[k] x p[j]
                // これら2つの行列を掛け合わせるコストは p[i-1] * p[k] * p[j]

                long long cost = dp[i][k] + dp[k+1][j] + (long long)p[i-1] * p[k] * p[j];
                dp[i][j] = MIN(dp[i][j], cost);
            }
        }
    }

    printf("%lld\n", dp[1][n]);

    return 0;
}