#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
} Node;

Node *root = NULL;


/*
insert : 値を二分探索木に挿入
計算量：O(height) 最悪でO(n)
*/
void insert(int key) {
    Node *y = NULL; // 探索用ポインタ
    Node *x = root; // yの親ノード
    Node *z = (Node *)malloc(sizeof(Node)); // 新しく挿入するノード
    z->key = key;
    z->left = NULL;
    z->right = NULL;

    // 挿入するノードは常に葉ノードになる．
    //つまり，yは挿入するノードの親ノードになる．
    while (x != NULL) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y; // 挿入するノードの親を決定

    // yの左の子か，右の子かを決定
    if (y == NULL) {
        root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
}

/*
inorder : 中間順巡回
計算量：O(n)
*/
void inorder(Node *T) {
    if (T != NULL) {
        inorder(T->left);
        printf(" %d", T->key);
        inorder(T->right);
    }
}

/*
preorder : 先行順巡回
計算量：O(n)
*/
void preorder(Node *T) {
    if (T != NULL) {
        printf(" %d", T->key);
        preorder(T->left);
        preorder(T->right);
    }
}

int main() {
    int m;
    scanf("%d", &m);

    char command[10];
    int value;

    for (int i = 0; i < m; i++) {
        scanf("%s", command);
        if (strcmp(command, "insert") == 0) {
            scanf("%d", &value);
            insert(value);
        } else if (strcmp(command, "print") == 0) {
            inorder(root);
            printf("\n");
            preorder(root);
            printf("\n");
        }
    }

    return 0;
}
