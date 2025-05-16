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
search : 値を二分探索木から探索
計算量：O(height) 最悪でO(n)　（平衡二分木であればO(logn)）
*/
Node *find(Node *u, int key) {
    while (u != NULL && u->key != key) {
        if (key < u->key) {
            u = u->left;
        } else {
            u = u->right;
        }
    }
    return u; // 見つからなければNULLを返す
}

/*
inorder : 中間順巡回
計算量：O(n)
*/
void inorder(Node *u) {
    if (u != NULL) {
        inorder(u->left);
        printf(" %d", u->key);
        inorder(u->right);
    }
}

/*
preorder : 先行順巡回
計算量：O(n)
*/
void preorder(Node *u) {
    if (u != NULL) {
        printf(" %d", u->key);
        preorder(u->left);
        preorder(u->right);
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
        } else if (strcmp(command, "find") == 0) {
            scanf("%d", &value);
            Node *found = find(root, value);
            printf(found != NULL ? "yes\n" : "no\n");
        }
    }

    return 0;
}
