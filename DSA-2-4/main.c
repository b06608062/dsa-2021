#include <stdio.h>

int main() {
    int n, w, l, r;
    int find = 0;
    scanf("%d", &n);
    int ary[n + 1][2];
    ary[1][0] = 0;
    ary[1][1] = 1000000000;
    for (int i = 1; i <= n ; i++) {
        scanf("%d%d%d", &w, &l, &r);
        int *p1 = &ary[i][0];
        int *p2 = &ary[i][1];
        if (w >= *p1 && w <= *p2) find++;
        if (l != -1) {
            ary[l][0] = *p1;
            ary[l][1] = *p2 > w ? w : *p2;
        }
        if( r != -1) {
            ary[r][0] = *p1 > w ? *p1 : w;
            ary[r][1] = *p2;
        }
    }
    printf("%d", find);

    return 0;
}