#include <stdio.h>
#include <string.h>

typedef struct {
    char suit;
    int value;
    int originalIndex;
} Card;

void swap(Card *a, Card *b) {
    Card temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Card A[], int p, int r) {
    int pivot = A[r].value;
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j].value <= pivot) {
            i++;
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i + 1], &A[r]);
    return i + 1;
}

void quicksort(Card A[], int p, int r) {
    if (p < r) {
        int q = partition(A, p, r);
        quicksort(A, p, q - 1);
        quicksort(A, q + 1, r);
    }
}

void checkStable(Card sorted[], Card original[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (sorted[i].value != sorted[j].value) break;

            // 同じ値で、順序が逆転してたら安定でない
            for (int k = 0; k < n - 1; k++) {
                if (original[k].value == sorted[i].value && original[k].suit == sorted[j].suit) {
                    printf("Not stable\n");
                    return;
                } else if (original[k].value == sorted[i].value && original[k].suit == sorted[i].suit) {
                    break;
                }
            }
        }
    }
    printf("Stable\n");
}

void printCards(Card cards[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%c %d\n", cards[i].suit, cards[i].value);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    Card cards[n], original[n];

    for (int i = 0; i < n; i++) {
        scanf(" %c %d", &cards[i].suit, &cards[i].value);
        cards[i].originalIndex = i;
        original[i] = cards[i];
    }

    quicksort(cards, 0, n - 1);
    checkStable(cards, original, n);
    printCards(cards, n);

    return 0;
}
