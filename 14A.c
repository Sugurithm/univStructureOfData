#include <stdio.h>
#include <string.h>

void match(char T[], char P[]) {
    int Tlen = strlen(T);
    int Plen = strlen(P);

    for (int i = 0; i < Tlen - Plen + 1; i++) {
        // strncmp(比較文字列1, 比較文字列2, 比較する文字数)
        if (strncmp(&T[i], P, Plen) == 0) {
            printf("%d\n", i);
        }
    }
}

int main(void) {
    char T[1001];
    char P[1001];

    scanf("%s", T);
    scanf("%s", P);

    match(T, P);
    return 0;
}