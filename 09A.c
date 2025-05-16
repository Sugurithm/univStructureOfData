#include <stdio.h>
#include <stdlib.h>

int main() {
    int H;
    scanf("%d", &H);
    
    int treeList[H];

    for (int i = 0; i < H; i++) {
        scanf("%d", &treeList[i]);
    }

    // 完全二分木の構造を考慮して値を出力する．
    for (int i = 0; i < H; i++) {
        printf("node %d: key = %d, ", i + 1, treeList[i]);

        if (i != 0) {
            printf("parent key = %d, ", treeList[(i - 1) / 2]);
        }

        if (2 * i + 1 < H) {
            printf("left key = %d, ", treeList[2 * i + 1]);
        }

        if (2 * i + 2 < H) {
            printf("right key = %d, ", treeList[2 * i + 2]);
        }

        printf("\n"); // 各ノード情報の終わりで改行
    }

    return 0;
}
