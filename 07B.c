#include <stdio.h>

#define MAX 100000

typedef struct {
    int parent; // 親
    int left;   // 左の子
    int right;  // 右の子
} Node;

Node tree[MAX];

int siblings(int u) {
    int p = tree[u].parent;
    if (p == -1) { // 自分自身が親でない
        return -1;
    } else if (tree[p].left == u && tree[p].right != -1) { // 自分自身が左の子
        return tree[p].right;
    } else if (tree[p].right == u && tree[p].right != -1) { // 自分自身が右の子
        return tree[p].left;
    } else {
        return -1;
    }
}

int degree(int u) { // 子の数
    int d = 0;
    if (tree[u].left != -1) d++;
    if (tree[u].right != -1) d++;
    return d;
}

int depth(int u) {
    int d = 0;
    while (tree[u].parent != -1) {
        u = tree[u].parent;
        d++;
    }
    return d;
}

int height(int u) { // 葉ノードからの最大距離．再帰関数...左下と右下のルートを比較し，最大値を更新
    int h = 0;
    int leftroot = 0, rightroot = 0;
    if (tree[u].left != -1) leftroot = height(tree[u].left) + 1;
    if (tree[u].right != -1) rightroot = height(tree[u].right) + 1;
    return h = leftroot > rightroot ? leftroot : rightroot;
}

char* type(int u) {
    if (tree[u].parent == -1) {
        return "root";
    } else if (tree[u].left == -1 && tree[u].right == -1) {
        return "leaf";
    } else {
        return "internal node";
    }
}

int main() {
    // 入力
    int n;
    scanf("%d", &n);

    // 初期化
    for (int i = 0; i < n; i++) {
        tree[i].parent = -1;
        tree[i].left = -1;
        tree[i].right = -1;
    }
    
    for (int i = 0; i < n; i++) {
        int id, l, r;
        scanf("%d %d %d", &id, &l, &r);
        if (l != -1) {
            tree[l].parent = id;
            tree[id].left = l;
        }
        if (r != -1) {
            tree[r].parent = id;
            tree[id].right = r;
        }
    }

    // 出力 node 0: parent = -1, sibling = -1, degree = 2, depth = 0, height = 3, root

    for (int i = 0; i < n; i++) {
        printf("node %d: parent = %d, sibling = %d, degree = %d, depth = %d, height = %d, %s\n", i, tree[i].parent, siblings(i), degree(i), depth(i), height(i), type(i));
    }

    return 0;
}

