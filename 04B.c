#include <stdio.h>

int binary_search(int a[], int n, int key) {
    int left = 0;
    int right = n;
    while (left < right) {
        int mid = (left + right) / 2;
        if (a[mid] == key) {
            return 1; // 見つけた場合1を返す
        } else if (key < a[mid]) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return 0; // 見つからなかった
}

int main(void) {
    int n, q;
    scanf("%d", &n);

    int S[n];
    for (int i = 0; i < n; i++) { scanf("%d", &S[i]);}

    scanf("%d", &q);
    int T[q];
    for (int i = 0; i < q; i++) { scanf("%d", &T[i]); }

    int count = 0;
    for (int i = 0; i < q; i++) {
        if (binary_search(S, n, T[i])) {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}