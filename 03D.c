#include <stdio.h>

#define MAX 2000

typedef struct {
    int data[MAX];
    int top;
} Stack;

typedef struct {
    int left[MAX];
    int area[MAX];
    int top;
} AreaStack;

int isEmptyInt(Stack *s) {
    return s->top == -1;
}

void pushInt(Stack *s, int x) {
    s->data[s->top] = x;
    s->top++;
}

int popInt(Stack *s) {
    s->top--;
    return s->data[s->top];
}

void pushArea(AreaStack *s, int left, int area) {
    s->left[s->top] = left;
    s->area[s->top] = area;
    s->top++;
}

int main() {
    char str[MAX + 1];
    fgets(str, sizeof(str), stdin);

    Stack slashStack = {.top = -1};
    AreaStack areaStack = {.top = -1};

    int total = 0;

    // 文字を1文字ずつ見ていく
    for (int i = 0; str[i] != '\0' && str[i] != '\n'; i++) {
        // "\"が出てきたらプッシュ
        if (str[i] == '\\') {
            pushInt(&slashStack, i);
        // "/"が出てきたらポップ
        } else if (str[i] == '/') {
            if (!isEmptyInt(&slashStack)) {
                // "/"に対応する "\" の位置を取得
                int j = popInt(&slashStack);
                int a = i - j;
                total += a; // 面積を加算

                while (areaStack.top >= 0 && areaStack.left[areaStack.top - 1] > j) {
                    a += areaStack.area[areaStack.top];
                    areaStack.top--;
                }

                pushArea(&areaStack, j, a);
            }
        }
    }

    printf("%d\n", total);
    if (areaStack.top == -1) {
        printf("0\n");
    } else {
        printf("%d", areaStack.top + 1);
        for (int i = 0; i <= areaStack.top; i++) {
            printf(" %d", areaStack.area[i]);
        }
        printf("\n");
    }

    return 0;
}