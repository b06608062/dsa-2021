#include <stdio.h>
#include <stdlib.h>

typedef struct cabin {
    int c_id;
    struct cabin *nxt_cabin, *pre_cabin;
} cabin;

typedef cabin *ptr;

void enter(ptr rails[], int r, int l) {
    ptr c = (ptr) malloc(sizeof(cabin));
    c->c_id = l;
    if (rails[r * 2] == NULL) {
        rails[r * 2] = c;
        rails[r * 2 + 1] = c;
        c->pre_cabin = NULL;
        c->nxt_cabin = NULL;
    } else if (rails[r * 2] == rails[r * 2 + 1]) {
        c->pre_cabin = rails[r * 2 + 1];
        c->nxt_cabin = NULL;
        rails[r * 2 + 1]->nxt_cabin = c;
        rails[r * 2 + 1] = c;
    } else {
        if (rails[r * 2 + 1]->nxt_cabin == NULL) {
            c->pre_cabin = rails[r * 2 + 1];
            c->nxt_cabin = NULL;
            rails[r * 2 + 1]->nxt_cabin = c;
            rails[r * 2 + 1] = c;
        } else {
            c->nxt_cabin = rails[r * 2 + 1];
            c->pre_cabin = NULL;
            rails[r * 2 + 1]->pre_cabin = c;
            rails[r * 2 + 1] = c;
        }
    }
}

void leave(ptr rails[], int r) {
    if (rails[r * 2] == NULL) return;
    ptr t = rails[r * 2 + 1];
    if (rails[r * 2] == t) {
        rails[r * 2] = NULL;
        rails[r * 2 + 1] = NULL;
    } else if (t->nxt_cabin == NULL) {
        rails[r * 2 + 1] = t->pre_cabin;
        if (t->pre_cabin->nxt_cabin == t)
            t->pre_cabin->nxt_cabin = NULL;
        else
            t->pre_cabin->pre_cabin = NULL;
    } else {
        rails[r * 2 + 1] = t->nxt_cabin;
        if (t->nxt_cabin->pre_cabin == t)
            t->nxt_cabin->pre_cabin = NULL;
        else
            t->nxt_cabin->nxt_cabin = NULL;
    }
    free(t);
}

void migrate(ptr rails[], int ra, int rb) {
    if (rails[ra * 2] == NULL) {
        return;
    }
    if (rails[rb * 2] == NULL) {
        rails[rb * 2] = rails[ra * 2 + 1];
    } else {
        ptr a = rails[ra * 2 + 1];
        ptr b = rails[rb * 2 + 1];
        if (b->nxt_cabin == NULL) {
            b->nxt_cabin = a;
            if (a->nxt_cabin == NULL)
                a->nxt_cabin = b;
            else
                a->pre_cabin = b;
        } else {
            b->pre_cabin = a;
            if (a->nxt_cabin == NULL)
                a->nxt_cabin = b;
            else
                a->pre_cabin = b;
        }
    }
    rails[rb * 2 + 1] = rails[ra * 2];
    rails[ra * 2] = NULL;
    rails[ra * 2 + 1] = NULL;
}

int main() {
    int k, n;
    scanf("%d%d", &k, &n);
    ptr rails[k][2];
    for (int i = 0; i < k; i++) {
        ptr bot = NULL;
        ptr top = NULL;
        rails[i][0] = bot;
        rails[i][1] = top;
    }

    char instr[10];
    int a, b;
    int line = 0;
    while (line++ < n) {
        scanf("%s", instr);
        switch (instr[0]) {
            case 'e':
                scanf("%d%d", &a, &b);
                enter(&rails[0][0], a, b);
                break;
            case 'l':
                scanf("%d", &a);
                leave(&rails[0][0], a);
                break;
            case 'm':
                scanf("%d%d", &a, &b);
                migrate(&rails[0][0], a, b);
                break;
        }
    }

    for (int i = 0; i < k; i++) {
        ptr t = rails[i][0];
        if (t != NULL) {
            printf("%d ", t->c_id);
            if (t->nxt_cabin != NULL || t->pre_cabin != NULL) {
                ptr u = t;
                if (t->nxt_cabin == NULL)
                    t = t->pre_cabin;
                else
                    t = t->nxt_cabin;
                while (t != NULL) {
                    printf("%d ", t->c_id);
                    if (t->nxt_cabin == u) {
                        u = t;
                        t = t->pre_cabin;
                    } else {
                        u = t;
                        t = t->nxt_cabin;
                    }
                }
            }
        }
        printf("\n");
    }

    return 0;
}
