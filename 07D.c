#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int left;
    int right;
} Node;

int findIndex(int *arr, int start, int end, int target) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}


/*
preorder 先行順巡回の先頭が木（部分木) の根とであり，
根の次の inorder 中間順巡回 のノードの値に対して，値ノードまでの値を CH[n] すると，
それまでのノードは根ノードの左に連続する形となる．
*/
// buildTree(木のポインタ, 前順巡回, 中間順巡回, 前順巡回の開始インデックス, 前順巡回の終了インデックス, 中間順巡回の開始インデックス, 中間順巡回の終了インデックス)
int buildTree(Node *tree, int *preorder, int *inorder, int preStart, int preEnd, int inStart, int inEnd) {
    if (preStart > preEnd || inStart > inEnd) return -1;

    int rootVal = preorder[preStart]; // preorder の先頭が木の根となる．
    int rootIndex = findIndex(inorder, inStart, inEnd, rootVal);
    int leftSize = rootIndex - inStart; // 左の子の数

    int rootIdx = preStart;
    tree[rootIdx].value = rootVal;

    tree[rootIdx].left = buildTree(tree, preorder, inorder, preStart + 1, preStart + leftSize, inStart, rootIndex - 1);
    tree[rootIdx].right = buildTree(tree, preorder, inorder, preStart + leftSize + 1, preEnd, rootIndex + 1, inEnd);

    return rootIdx;
}

void postorder(Node *tree, int node, int *postorderList, int *index) {
    if (node == -1) return;
    postorder(tree, tree[node].left, postorderList, index);
    postorder(tree, tree[node].right, postorderList, index);
    postorderList[*index] = tree[node].value;
    (*index)++;
}


int main() {
    int n;
    scanf("%d", &n);

    int preorder[n], inorder[n];
    Node tree[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &preorder[i]);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &inorder[i]);
    }

    for (int i = 0; i < n; i++) {
        tree[i].left = -1;
        tree[i].right = -1;
    }

    int root = buildTree(tree, preorder, inorder, 0, n - 1, 0, n - 1);
    int postorderList[n];
    for (int i = 0; i < n; i++) {
        postorderList[i] = -1;
    }
    int index = 0;
    postorder(tree, root, postorderList, &index);

    printf("%d", postorderList[0]);
    for (int i = 1; i < n; i++) {
        printf(" %d", postorderList[i]);
    }
    printf("\n");

    return 0;
}
