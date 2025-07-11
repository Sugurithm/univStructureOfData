#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 500000
#define INFTY 2000000000 // 10^9 より十分大きい値

long long ans = 0;

// 最大サイズは n/2 + 1，番兵のため +1
int L[MAX_N / 2 + 2]; 
int R[MAX_N / 2 + 2]; 


// 2つのソート済み部分配列をマージする関数
void merge(int A[], int left, int mid, int right) {
    int n1 = mid - left;
    int n2 = right - mid;

    // L[0...n1-1], R[0...n2-1] を生成
    for (int i = 0; i < n1; i++) {
        L[i] = A[left + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = A[mid + i];
    }

    L[n1] = INFTY;
    R[n2] = INFTY;

    int i = 0;
    int j = 0;

    // A[left...right-1] にソート済みの要素を配置
    /*
    番兵を設定することで，条件分岐を増やすことなく，コピーすることができる．
    もしLが空になりiがn1となると，INFTYになる．
    次の比較としては　R[j] < INFTYとなることが保証される．
    */
    for (int k = left; k < right; k++) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i = i + 1;
        } else {
            A[k] = R[j];
            j = j + 1;
            ans += n1 - i;
        }
    }
}

void mergeSort(int A[], int left, int right) {
    if (left + 1 < right) {
        int mid = (left + right) / 2;
        mergeSort(A, left, mid);
        mergeSort(A, mid, right);
        merge(A, left, mid, right);
    }
}

int main(void) {
    int n;
    scanf("%d", &n);
    int S[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d", &S[i]);
    }

    mergeSort(S, 0, n);

    printf("%lld\n", ans);

    return 0;
}