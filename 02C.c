#include <stdio.h>

typedef struct {
    char suit;
    int value;
} Card;

void swap(Card *a, Card *b) {
    Card tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubbleSort(Card A[], int N) {
    int flag = 1;
    while (flag) {
        flag = 0;
        for (int i = N - 1; i > 0; i--) {
            if (A[i].value < A[i - 1].value) {
                swap(&A[i], &A[i - 1]);
                flag = 1;
            }
        }
    }
}

void selectionSort(Card A[], int N) {
    for (int i = 0; i < N - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < N; j++) {
            if (A[j].value < A[min_index].value) {
                min_index = j;
            }
        }
        if (min_index != i) { // 同じもの同士のスワップはしない
            swap(&A[i], &A[min_index]);
        }
    }
}

// バブルソートが安定ソートであることを用いて判定する．
int isStableByBubbleSort(Card bubbleSorted[], Card selectionSorted[], int N) {
    for (int i = 0; i < N; i++) {
        if (bubbleSorted[i].suit != selectionSorted[i].suit) {
            return 0;
        }
    }
    return 1;
}

void printCards(Card A[], int N) {
    for (int i = 0; i < N; i++) {
        if (i != 0) printf(" ");
        printf("%c%d", A[i].suit, A[i].value);
    }
    printf("\n");
}

int main() {
    int N;
    scanf("%d", &N);
    Card A[N];
    for (int i = 0; i < N; i++) {
        scanf(" %c%d", &A[i].suit, &A[i].value);
    }
    Card bubbleSorted[N];
    Card selectionSorted[N];
    for (int i = 0; i < N; i++) {
        bubbleSorted[i] = A[i];
        selectionSorted[i] = A[i];
    }

    // ソート
    bubbleSort(bubbleSorted, N);
    selectionSort(selectionSorted, N);

    // 出力
    printCards(bubbleSorted, N);
    printf("Stable\n");

    printCards(selectionSorted, N);
    if (isStableByBubbleSort(bubbleSorted, selectionSorted, N)) {
        printf("Stable\n");
    } else {
        printf("Not stable\n");
    }
    return 0;
}