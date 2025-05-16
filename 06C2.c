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

int partition(Card card[], int left, int right) {
    int pivotValue = card[right].value; // 右をpivotとする
    int i = left - 1; // pivotより小さい値を格納するindex，最終的にpivotと入れ替わる
    for (int j = left; j < right; j++) {
        if (card[j].value <= pivotValue) { 
            i++;
            swap(&card[i], &card[j]);
        }
    }
    swap(&card[i + 1], &card[right]);
    return i + 1;
}

void quicksort(Card card[], int left, int right) {
    if (left < right) {
        int pivot = partition(card, left, right);
        quicksort(card, left, pivot - 1);
        quicksort(card, pivot + 1, right);
    }
}

void isStable(Card sorted[], Card original[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (sorted[i].value == sorted[j].value) {
                // 元の順序で sorted[j].suit が sorted[i].suit より先に来ていたら不安定
                for (int k = 0; k < n; k++) {
                    if (original[k].value == sorted[i].value) {
                        if (original[k].suit == sorted[j].suit) {
                            printf("Not stable\n");
                            return;
                        }
                        if (original[k].suit == sorted[i].suit) {
                            break;
                        }
                    }
                }
            }
        }
    }
    printf("Stable\n");
}


void showCards(Card cards[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%c %d\n", cards[i].suit, cards[i].value);
    }
}

int main(void) {
    // input
    int n;
    scanf("%d", &n);

    Card cards[n];
    Card originalCards[n];
    for (int i = 0; i < n; i++) {
        // scanf("%c %d", &cards[i].suit, &cards[i].value);
        scanf(" %c %d", &cards[i].suit, &cards[i].value);
        originalCards[i] = cards[i];
    }

    // quick sort algorithm
    quicksort(cards, 0, n - 1);

    // output
    isStable(cards, originalCards, n);
    showCards(cards, n);

    return 0;
}