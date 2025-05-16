// コッホ曲線

#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

void koch(int d, Point p1, Point p2){
    if (d == 0) {
        printf("%.8f %.8f\n", p1.x, p1.y);
        return;
    }

    Point s, t, u;
    s.x = (2.0 * p1.x + p2.x) / 3.0;
    s.y = (2.0 * p1.y + p2.y) / 3.0;
    t.x = (p1.x + 2.0 * p2.x) / 3.0;
    t.y = (p1.y + 2.0 * p2.y) / 3.0;

    double angle = M_PI / 3.0;
    double dx = t.x - s.x;
    double dy = t.y - s.y;

    u.x = cos(angle) * dx - sin(angle) * dy + s.x;
    u.y = sin(angle) * dx + cos(angle) * dy + s.y;

    koch(d - 1, p1, s);
    koch(d - 1, s, u);
    koch(d - 1, u, t);
    koch(d - 1, t, p2);

}

int main(void) {
    int n;
    scanf("%d", &n);

    Point start = {0.0, 0.0};
    Point end = {100.0, 0.0};

    koch(n, start, end);
    printf("%.8f %.8f\n", end.x, end.y);

    return 0;
}