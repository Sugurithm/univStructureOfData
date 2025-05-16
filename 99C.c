#include <stdio.h>

int main() {
    int height, width;
    scanf("%d %d", &height, &width);
    
    int area = height * width;
    int length = 2 * (height + width);
    printf("%d %d\n", area, length);

    return 0;
}