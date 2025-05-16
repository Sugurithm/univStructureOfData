#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

typedef struct {
    int value; // 値
    int parent; // 親
    int left;   // 左の子
    int right;  // 右の子
} Node;

Node* tree;

// preorder 先行順巡回
void preorder(Node* node, int rootIndex) {
    printf(" %d", node[rootIndex].value);
    if (node[rootIndex].left != -1) {
        preorder(node, node[rootIndex].left);
    }
    if (node[rootIndex].right != -1) {
        preorder(node, node[rootIndex].right);
    }
}

// inorder　中間順巡回
void inorder(Node* node, int rootIndex) {
    if (node[rootIndex].left != -1) {
        inorder(node, node[rootIndex].left);
    }
    printf(" %d", node[rootIndex].value);
    if (node[rootIndex].right != -1) {
        inorder(node, node[rootIndex].right);
    }
}

// postorder　後行順巡回
void postorder(Node* node, int rootIndex) {
    if (node[rootIndex].left != -1) {
        postorder(node, node[rootIndex].left);
    }
    if (node[rootIndex].right != -1) {
        postorder(node, node[rootIndex].right);
    }
    printf(" %d", node[rootIndex].value);
}

int main() {
    // 入力
    int n, root;
    scanf("%d", &n);

    // メモリ確保
    tree = (Node*)malloc(sizeof(Node) * n);

    // 初期化
    for (int i = 0; i < n; i++) {
        tree[i].value = i;
        tree[i].parent = -1;
        tree[i].left = -1;
        tree[i].right = -1;
    }

    // 入力と木構造の構築
    for (int i = 0; i < n; i++) {
        int id, left, right;
        scanf("%d %d %d", &id, &left, &right);
        if (left != -1) {
            tree[left].parent = id;
            tree[id].left = left;
        }
        if (right != -1) {
            tree[right].parent = id;
            tree[id].right = right;
        }
    }

    // 根を探す
    for (int i = 0; i < n; i++) {
        if (tree[i].parent == -1) {
            root = i;
            break;
        }
    }

    // 出力
    printf("Preorder\n");
    preorder(tree, root);
    printf("\n");

    printf("Inorder\n");
    inorder(tree, root);
    printf("\n");

    printf("Postorder\n");
    postorder(tree, root);
    printf("\n");

    // メモリ解放
    free(tree);
    tree = NULL;
    return 0;
}