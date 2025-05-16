#include <stdio.h>
#include <stdlib.h>

void CountingSort(int A[], int B[], int n, int k) {
    int C[k];
    for (int j = 0; j < n; j++) {
        C[A[j]]++;
    }

    for (int i = 1; i < k; i++) {
        C[i] = C[i] + C[i - 1];
    }

    for (int j = n - 1; j >= 0; j--) {
        B[C[A[j]] - 1] = A[j];
        C[A[j]]--;
    }
}

int main(void) {
    int n;
    scanf("%d", &n);

    int A[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    // 最大値を見つける（k を決定する）
    int max = A[0];
    for (int i = 1; i < n; i++) {
        if (A[i] > max) max = A[i];
    }

    int B[n];
    CountingSort(A, B, n, max + 1);

    for (int i = 0; i < n; i++) {
        printf("%d ", B[i]);
    }
    printf("\n");

    return 0;
}
