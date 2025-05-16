#include <stdio.h>

#define MAX 100000

typedef struct {
    int parent; // 親
    int left;   // 最も左の子
    int right;  // すぐ右の兄弟
    int depth;
} Node;

Node tree[MAX];

void setDepth(int u, int d) {
    tree[u].depth = d;
    if (tree[u].left != -1) setDepth(tree[u].left, d + 1); // 最も左の子は深さ+1
    if (tree[u].right != -1) setDepth(tree[u].right, d);   // 右兄弟は同じ深さ
}

void printChildren(int u) {
    printf("[");
    int first = 1; // 最初か否かのフラグ
    for (int child = tree[u].left; child != -1; child = tree[child].right) {
        if (!first) printf(", ");
        printf("%d", child);
        first = 0;
    }
    printf("]\n");
}

int main() {
    int n;
    scanf("%d", &n);

    // 初期化
    for (int i = 0; i < n; i++) {
        tree[i].parent = -1;
        tree[i].left = -1;
        tree[i].right = -1;
        tree[i].depth = -1;
    }

    // 入力と木構造の構築
    for (int i = 0; i < n; i++) {
        int id, k; // id : ノード番号（親）, k : 子の数
        scanf("%d %d", &id, &k);
        int prev = -1; // 前のノードを覚えておく
        for (int j = 0; j < k; j++) {
            int child;
            scanf("%d", &child);
            tree[child].parent = id; // 親子関係を構築
            if (j == 0) {
                tree[id].left = child; // 親（id)の最も左の子
            } else {
                tree[prev].right = child; // 兄弟関係を構築
            }
            prev = child; // ノードを更新
        }
    }

    // 根を探す
    int root = -1;
    for (int i = 0; i < n; i++) {
        if (tree[i].parent == -1) {
            root = i;
            break;
        }
    }

    setDepth(root, 0);

    // 出力 node, parent, depth, type, children
    for (int i = 0; i < n; i++) {
        printf("node %d: parent = %d, depth = %d, ", i, tree[i].parent, tree[i].depth);

        if (tree[i].parent == -1) {
            printf("root, ");
        } else if (tree[i].left == -1) {
            printf("leaf, ");
        } else {
            printf("internal node, ");
        }

        printChildren(i);
    }

    return 0;
}
