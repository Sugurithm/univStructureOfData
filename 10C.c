#include <stdio.h>
#include <string.h>

int dp[1001][1001];

int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

void lcs(char X[], char Y[]) {
    int xLen = strlen(X);
    int yLen = strlen(Y);
    for (int i = 1; i <= xLen; i++) {
        for (int j = 1; j <= yLen; j++) {
            if (X[i - 1] == Y[j - 1]) {
                // 一致する場合，lcsの長さを1増やす
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                // Xのi-1文字目とYのj-1文字目を比較
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
}

int main(void) {
    int q;
    scanf("%d", &q);
    char X[1001], Y[1001];
    for (int i = 0; i < 1001; i++) {
        for (int j = 0; j < 1001; j++) {
            dp[i][j] = 0;
        }
    }
    for (int i = 0; i < q; i++) {
        scanf("%s", X);
        scanf("%s", Y);
        lcs(X, Y);
        printf("%d\n", dp[strlen(X)][strlen(Y)]);
    }
    return 0;
}