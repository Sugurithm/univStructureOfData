#include <stdio.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int selectionSort(int A[], int N) {
    int count = 0;
    for (int i = 0; i < N - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < N; j++) {
            if (A[j] < A[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) { // 同じもの同士のスワップはしない
            swap(&A[i], &A[min_index]);
            count++;
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

    int swapCount = selectionSort(A, N);

    // 出力
    for (int i = 0; i < N; i++) {
        if (i != 0) printf(" ");
        printf("%d", A[i]);
    }
    printf("\n");

    printf("%d\n", swapCount);

    return 0;
}