// quick sort

#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef struct {
    char suit;
    int value;
    int index;
} Card;

void showArray(Card A[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%c %d\n", A[i].suit, A[i].value);
    }
}

void quicksort(Card A[], int n) {
    if (n <= 1) return;

    Card pivot = A[0];
    Card left[n];
    Card right[n];

    int left_index = 0;
    int right_index = 0;
    for (int i = 1; i < n; i++) {
        if (A[i].value < pivot.value) {
            left[left_index] = A[i];
            left_index++;
        } else if (A[i].value > pivot.value) {
            right[right_index] = A[i];
            right_index++;
        } else {
            if (A[i].index < pivot.index) {
                left[left_index] = A[i];
                left_index++;
            } else {
                right[right_index] = A[i];
                right_index++;
            }
        }
    }

    quicksort(left, left_index);
    quicksort(right, right_index);

    for (int i = 0; i < left_index; i++) {
        A[i] = left[i];
    }
    A[left_index] = pivot;
    for (int i = 0; i < right_index; i++) {
        A[left_index + i + 1] = right[i];
    }
    
}

void is_stable(Card A[], Card B[], int n) {
    int isStable = 1;
    for (int i = 0; i < n; i++) {
        if (A[i].suit != B[i].suit) {
            isStable = 0;
        }
    }

    if (isStable) {
        printf("Stable\n");
    } else {
        printf("Not stable\n");
    }
}


int main(void) {
    int n;
    scanf("%d", &n);

    Card A[n];
    Card B[n];
    for (int i = 0; i < n; i++) {
        scanf("%s %d", &A[i].suit, &A[i].value);
        A[i].index = i;
        B[i] = A[i];
    }

    quicksort(A, n);

    is_stable(A, B, n);
    showArray(A, n);

    return 0;
}