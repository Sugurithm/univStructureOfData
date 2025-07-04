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
treeMin : xノードを節とする部分木の最小ノードを返す
計算量：O(height)
*/
Node *treeMin(Node *x) {
    while (x->left != NULL) {
        x = x->left;
    }
    return x;
}

/*
treeSuccessor : xの次に大きいノードを返す
*/
Node *treeSuccessor(Node *x) {
    if (x->right != NULL) {
        return treeMin(x->right);
    }
    /*
    今回のアルゴリズムでは x->right == NULL になることはないが，
    他の場合で使われることがあるので，汎用性を考慮して実装する．
    （二分木のアルゴリズムなので，子が二つのノードを削除する場合に焦点を当てている）
    */
    Node *y = x->parent;
    while (y != NULL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

void treeDelete(Node *z) {
    Node *y = NULL; // 実際に削除するノード（z or zの後継ノード）
    Node *x = NULL; // yの子ノード（yが削除された時に，親との関係を再構築するために必要）

    /*
    1. 子が0 or 1 -> z自身を削除
    2. 子が2 -> zの後継ノード（zの次に大きいノード）を削除
    */
    if (z->left == NULL || z->right == NULL) {
        y = z;
    } else {
        y = treeSuccessor(z); // zの右部分木の中で最小のノード
    }

    // yの子ノードを決定
    // yは最大で1つの子ノードを持つ
    // -> 後継ノードはzの右部分木の最小ノードなので，y->leftはNULL
    if (y->left != NULL) {
        x = y->left;
    } else {
        x = y->right;
    }

    // xがNULLでないなら，xの親をyの親にする．
    if (x != NULL) {
        x->parent = y->parent;
    }

    // yと親の関係を削除し，xの親をyの親にする
    if (y->parent == NULL) {
        // yがrootの場合，rootを更新
        root = x;
    } else if (y == y->parent->left) {
        // yが親の左の子の場合，xを親の左の子にする
        y->parent->left = x;
    } else {
        // yが親の右の子の場合，xを親の右の子にする
        y->parent->right = x;
    }

    /*
    子が2の場合，yのkeyをzのkeyにする．
    yはzの後継ノードなので，yのkeyだけをzにコピーすれば良い．中身がyに置き換わる（yはすでに構造から外れている）．
    */
    if (y != z) {
        z->key = y->key;
    }

    free(y);
    y = NULL;
    x = NULL;
    z = NULL;
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
        } else if (strcmp(command, "delete") == 0) {
            scanf("%d", &value);
            Node *found = find(root, value);
            if (found != NULL) {
                treeDelete(found);
            }
        }
    }

    return 0;
}
