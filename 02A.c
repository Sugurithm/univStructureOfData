#include <stdio.h>

#define TRUE 1
#define FALSE 0

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int bubbleSort(int A[], int N) {
    /* 配列が既に整列済みであれば早期に終了可能 */
    int flag = TRUE;
    int count = 0;
    while (flag) {
        flag = FALSE;
        for (int i = N - 1; i > 0; i--) {
            if (A[i] < A[i - 1]) {
                swap(&A[i], &A[i - 1]);
                flag = TRUE;
                count++;
            }
        }
    }

    return count;
}

int main() {
    int N;
    scanf("%d", &N);
    int A[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    
    int swapCount = bubbleSort(A, N);

    // 出力
    for (int i = 0; i < N; i++) {
        if (i != 0) printf(" ");
        printf("%d", A[i]);
    }
    printf("\n");

    printf("%d\n", swapCount);

    return 0;
}