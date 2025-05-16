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

/*
insert : 値を二分探索木に挿入
計算量：O(height) 最悪でO(n)
*/
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

/*
search : 値を二分探索木から探索
計算量：O(height) 最悪でO(n)　（平衡二分木であればO(logn)）
*/
int search(Node *T, int value) {
    int me = root; 
    while (me != -1) {
        if (T[me].value == value) {
            return 1;
        } else if (T[me].value > value) {
            me = T[me].left;
        } else {
            me = T[me].right;
        }
    }

    return 0;
}

/*
delete : 値を二分探索木から削除
計算量：O(height) 最悪でO(n)
*/
void delete(Node *T, int value) {
    // 削除するノードを探索（me: 削除したい値を持つノード）
    int me = root;
    while (T[me].value != value) {
        if (T[me].value > value) {
            me = T[me].left;
        } else {
            me = T[me].right;
        }
    }

    // 削除するノードを決定．(delete_node: 実際に削除するノード)
    int delete_node;
    if (T[me].left == -1 || T[me].right == -1) { // 子が0 or 1の場合 -> そのまま削除
        delete_node = me;
    } else { // 子が2つある場合，右側のBSTの最小ノード（後継ノード）を探す．
        delete_node = T[me].right;
        while (T[delete_node].left != -1) {
            delete_node = T[delete_node].left;
        }
    }

    // 削除するノードの子を決定（0 or 1）
    int child;
    if (T[delete_node].left != -1) {
        child = T[delete_node].left;
    } else {
        child = T[delete_node].right;
    }

    // 子の親を更新
    if (child != -1) {
        T[child].parent = T[delete_node].parent;
    }

    // 削除するノードの親を更新（削除するノードの親の左 or 右に子をつける）
    if (T[delete_node].parent == -1) {
        root = child;
    } else if (T[T[delete_node].parent].left == delete_node) {
        T[T[delete_node].parent].left = child;
    } else {
        T[T[delete_node].parent].right = child;
    }
    
    // もし削除するノードが me とは別（後継ノードの場合），
    // 削除するノードの値を me にコピーする．
    if (delete_node != me) {
        T[me].value = T[delete_node].value;
    }


}

/*
inorder : 中間順巡回
計算量：O(n)
*/
void inorder(int root) {
    if (root != -1) {
        inorder(tree[root].left);
        printf(" %d", tree[root].value);
        inorder(tree[root].right);
    }
}

/*
preorder : 前順巡回
計算量：O(n)
*/
void preorder(int root) {
    if (root != -1) {
        printf(" %d", tree[root].value);
        preorder(tree[root].left);
        preorder(tree[root].right);
    }
}

int main() {
    int m;
    scanf("%d", &m);

    // メモリ確保 (O(m))
    tree = (Node*)malloc(sizeof(Node) * m);

    // 初期化 (O(m))
    for (int i = 0; i < m; i++) {
        tree[i].value = -1;
        tree[i].parent = -1;
        tree[i].left = -1;
        tree[i].right = -1;
    }

    char str[10];
    int value;

    // 入力 (O(m) * height)
    for (int i = 0; i < m; i++) {
        scanf("%s", str);
        if (strcmp(str, "insert") == 0) {
            scanf("%d", &value);
            insert(tree, value); // O(height)
        } else if (strcmp(str, "find") == 0) {
            scanf("%d", &value);
            if (search(tree, value)) { // O(height)
                printf("yes\n");
            } else {
                printf("no\n");
            }
        } else if (strcmp(str, "print") == 0) {
            inorder(root); // O(n)
            printf("\n");
            preorder(root); // O(n)
            printf("\n");
        } else if (strcmp(str, "delete") == 0) {
            scanf("%d", &value);
            delete(tree, value); // O(height)
        }
    }

    // メモリ解放
    free(tree);
    tree = NULL;
    return 0;
}