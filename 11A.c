#include <stdio.h>

void printArray(int n, int A[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j != 0) printf(" ");
            printf("%d", A[i][j]);
        }
        printf("\n");
    }
}

int main () {
    int n;
    scanf("%d", &n);
    
    int A[n][n];
    // 初期化 (O(n^2))
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = 0;
        }
    }

    // O(n^2)
    for (int i = 0; i < n; i++) {
        int u, k;
        scanf("%d %d", &u, &k);
        for (int j = 0; j < k; j++) {
            int adj;
            scanf("%d", &adj);
            A[i][adj - 1] = 1;
        }
    }

    // output (O(n^2))
    printArray(n, A);

}