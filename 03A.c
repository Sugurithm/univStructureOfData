#include <stdio.h>

int RPN(char stack[], int top) {
    int a, b;
    if (stack[top - 1] == '*') {
        a = RPN(stack, top - 1);
        b = RPN(stack, top - 2);
        return b * a;
    } else if (stack[top - 1] == '/') {
        a = RPN(stack, top - 1);
        b = RPN(stack, top - 2);
        return b / a;
    } else if (stack[top - 1] == '+') {
        a = RPN(stack, top - 1);
        b = RPN(stack, top - 2);
        return b + a;
    } else if (stack[top - 1] == '-') {
        a = RPN(stack, top - 1);
        b = RPN(stack, top - 2);
        return b - a;
    } else {
        return stack[top - 1] - '0'; // 数値型に変換
    }
}

int main() {
    char S[100];
    scanf("%s", S);
    printf("%d\n", RPN(S, strlen(S)));
    return 0;
}