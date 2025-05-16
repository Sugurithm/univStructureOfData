#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int value; // 値
    int parent; // 親
    int left;   // 左の子
    int right;  // 右の子
} Node;

Node* tree;
int root = -1;
int n = 0;

void insert(Node *T, int value) {
    int z = n++;
    T[z].value = value;
    T[z].left = -1;
    T[z].right = -1;

    /*
    挿入するノードは常に葉ノードになる．
    つまり，挿入するノード（me)の親の左につくか右につくかを判断する．
    初めに，自分が値ノードからスタートし，挿入すべきノードを探索する．
    その際に親ノードを更新し続ける．
    */
    int parent = -1;
    int me = root;
    while (me != -1) {
        parent = me;
        if (T[me].value > value) {
            me = T[me].left;
        } else {
            me = T[me].right;
        }
    }

    T[z].parent = parent; // 親を決定

    if (parent == -1) {
        root = z;
    } else if (T[parent].value > value) {
        T[parent].left = z;
    } else {
        T[parent].right = z;
    }
}

void inorder(int root) {
    if (root != -1) {
        inorder(tree[root].left);
        printf(" %d", tree[root].value);
        inorder(tree[root].right);
    }
}

void preoder(int root) {
    if (root != -1) {
        printf(" %d", tree[root].value);
        preoder(tree[root].left);
        preoder(tree[root].right);
    }
}

int main() {
    int m;
    scanf("%d", &m);

    // メモリ確保
    tree = (Node*)malloc(sizeof(Node) * m);

    // 初期化
    for (int i = 0; i < m; i++) {
        tree[i].value = -1;
        tree[i].parent = -1;
        tree[i].left = -1;
        tree[i].right = -1;
    }

    char str[10];
    int value;

    // 入力
    for (int i = 0; i < m; i++) {
        scanf("%s", str);
        if (strcmp(str, "insert") == 0) {
            scanf("%d", &value);
            insert(tree, value);
        } else if (strcmp(str, "print") == 0) {
            inorder(root);
            printf("\n");
            preoder(root);
            printf("\n");
        }
    }

    // メモリ解放
    free(tree);
    tree = NULL;
    return 0;
}