#include <stdio.h>

int cnt = 0; // 挿入ソートの交換回数
int G[100]; // シェルソートの間隔列
int m = 0; // 使用する間隔の数

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// 挿入ソート O(n^2 / g)
void insertionSort(int A[], int n, int gap) {
    for (int i = gap; i < n; i++) {
        int v = A[i]; // 比較元
        int j = i - gap; // 比較先（比較前より gap だけ前の要素）
        // A[i] と gap 間隔の要素を比較し．vより大きい要素があれば後ろにずらす．
        while (j >= 0 && A[j] > v) {
            A[j + gap] = A[j];
            j -= gap;
            cnt++;
        }
        A[j + gap] = v;
    }
}

// シェルソート  O(n^1.5)
void shellSort(int A[], int n) {
    int h = 1;
    // Knuthの間隔列を作成
    while (h <= n) {
        G[m++] = h;
        h = 3 * h + 1;
    }
    // gapの大きい順に挿入ソート
    for (int i = m - 1; i >= 0; i--) {
        int gap = G[i];
        insertionSort(A, n, gap);
    }
}

void printG(int m) {
    for (int i = m - 1; i >= 0; i--) {
        printf("%d ", G[i]);
    }
    printf("\n");
}

void printA(int A[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d\n", A[i]);
    }
}

int main() {
    // 入力
    int n;
    scanf("%d", &n);
    int A[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    // 処理
    shellSort(A, n);

    // 出力
    printf("%d\n", m);
    printG(m);
    printf("%d\n", cnt);
    printA(A, n);

    return 0;
}