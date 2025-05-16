#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    struct Node *prev;
    struct Node *next;
} Node;

Node *nil;

// [prev] <- [node] -> [next]
// [last] <- [nil] -> [first]

void init() {
    nil = (Node *)malloc(sizeof(Node));
    nil->next = nil;
    nil->prev = nil;
}

void insert(int x) {
    Node *node = (Node *)malloc(sizeof(Node));
    // 挿入するときに考えることは，前のノードのnextと後ろのノードのprevを変更すること．

    // 挿入するノードおよび前後のノードの更新
    node->key = x;
    node->prev = nil;
    node->next = nil->next;
    nil->next->prev = node;
    nil->next = node;
}

void delete(int x) {
    Node *node = nil->next;
    // 先頭から順に探索していく
    while (node != nil) {
        // 探索しているノードのkeyとxが一致したら
        // そのノードを削除する（前後のノードのnext, prevを変更する）
        if (node->key == x) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            free(node);
            return;
        }
        node = node->next;
    }
}

void deleteFirst() {
    // 先頭のノードを削除する
    if (nil->next == nil) return;
    Node *node = nil->next;
    nil->next = node->next;
    node->next->prev = nil;
    free(node);
}

void deleteLast() {
    // 末尾のノードを削除する
    if (nil->prev == nil) return;
    Node *node = nil->prev;
    nil->prev = node->prev;
    node->prev->next = nil;
    free(node);
}

void printList() {
    Node *node = nil->next;
    int flag = 1;
    while (node != nil) {
        if (flag) { // 最初の要素はスペースなしで出力
            printf("%d", node->key);
            flag = 0;
        } else {
            printf(" %d", node->key);
        }
        node = node->next;
    }
    printf("\n");
}

int main() {
    // 入力
    int n;
    scanf("%d", &n);
    
    // 初期化
    init();

    for (int i = 0; i < n; i++) {
        char command[20];
        scanf("%s", command);

        if (strcmp(command, "insert") == 0) {
            int x;
            scanf("%d", &x);
            insert(x);
        } else if (strcmp(command, "delete") == 0) {
            int x;
            scanf("%d", &x);
            delete(x);
        } else if (strcmp(command, "deleteFirst") == 0) {
            deleteFirst();
        } else if (strcmp(command, "deleteLast") == 0) {
            deleteLast();
        }
    }
    
    // 出力
    printList();
    return 0;
}