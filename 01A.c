#include <stdio.h>

// 配列を表示
void printArray(int A[], int N) { 
    for (int i = 0; i < N; i++) {
        if (i != 0) printf(" ");
        printf("%d", A[i]);
    }
    printf("\n");
}

// 挿入ソート
void insertionSort(int A[], int N) {
    printArray(A, N); // 初期状態

    for (int i = 1; i < N; i++) {
        int key = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
        printArray(A, N); // 各ステップ
    }
}

int main() {
    int N;
    scanf("%d", &N);
    int A[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    insertionSort(A, N);

    return 0;
}