#include <stdio.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void maxHeapify(int A[], int n, int i) {
    int left = 2 * i;
    int right = 2 * i + 1;

    /*
    最大値を持つノードを探す．
    まずは左のこと節iを比べる．その後に右の子を比べる
    */
    int largestNumIndex;
    if (left <= n && A[left] > A[i]) {
        largestNumIndex = left;
    } else {
        largestNumIndex = i;
    }

    if (right <= n && A[right] > A[largestNumIndex]) {
        largestNumIndex = right;
    }

    /*
    節iとその節の子の内，最大の値を持つノードが節iでなければ，
    その最大のノードとswapする．
    */
    if (largestNumIndex != i) {
        swap(&A[i], &A[largestNumIndex]);
        maxHeapify(A, n, largestNumIndex);

}
}

int main() {
    int H; // heap size
    scanf("%d", &H);
    
    int A[H + 1]; // heap array

    // max heapify
    for (int i = 1; i <= H; i++) {
        scanf("%d", &A[i]);
    }

    /*
    Heapifyアルゴリズムの引数は子を持つノード（節）であるため，
    H/2 ... 1 までで良い．（ H/2 ... H は全て葉ノードである）．
    */
    for (int i = H / 2; i >= 1; i--) {
        maxHeapify(A, H, i);
    }

    // output
    for (int i = 1; i <= H; i++) {
        printf(" %d", A[i]);
    }
    return 0;
}