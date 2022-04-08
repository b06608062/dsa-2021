#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char operator;
    struct node *nxt;
} node;
typedef node *ptr;
ptr top = NULL;

void push(char operator) {
    ptr t = (ptr) malloc(sizeof(node));
    t->operator = operator;
    t->nxt = top;
    top = t;
}

char pop() {
    if (top == NULL) return -1;
    ptr t = top;
    char operator = top->operator;
    top = top->nxt;
    free(t);
    return operator;
}

int compare_operator_priority(char operator) {
    if (top == NULL) return 1;
    int a, b;
    switch (operator) {
        case '+':
        case '-':
            a = 1;
            break;
        case '*':
        case '/':
            a = 2;
            break;
        default:  // '('
            a = 10;
    }
    switch (top->operator) {
        case '+':
        case '-':
            b = 1;
            break;
        case '*':
        case '/':
            b = 2;
            break;
        default:  // case '('
            b = 0;
    }
    return a > b ? 1 : -1;
}

double eval_postfix(char *postfix) {
    double stack[100000];
    int stack_top = -1;
    while (*postfix != '\0') {
        if (*postfix >= 48 && *postfix <= 57) {
            int temp = 0;
            while (*postfix >= 48 && *postfix <= 57) {
                temp = temp * 10 + (*postfix - 48);
                postfix++;
            }
            stack[++stack_top] = (double)temp;
        } else {
            double n2 = stack[stack_top--];
            double n1 = stack[stack_top--];
            double n3;
            switch (*postfix) {
                case '+':
                    n3 = n1 + n2;
                    break;
                case '-':
                    n3 = n1 - n2;
                    break;
                case '*':
                    n3 = n1 * n2;
                    break;
                default:  // case '/'
                    n3 = n1 / n2;
            }
            stack[++stack_top] = n3;
        }
        postfix++;
    }
    return stack[0];
}

int main() {
    char input[100000];
    while (scanf("%s", input) != EOF) {
        char postfix[100000];
        int idx = 0;
        char *p = input;
        while (*p != '\0') {
            if (*p >= 48 && *p <= 57) {
                while (*p >= 48 && *p <= 57) {
                    postfix[idx++] = *p;
                    p++;
                }
                postfix[idx++] = ',';
            } else {
                if (*p == ')') {
                    char c;
                    while ((c = pop()) != '(') postfix[idx++] = c;
                } else {
                    if (compare_operator_priority(*p) > 0) {
                        push(*p);
                    } else {
                        do {
                            postfix[idx++] = pop();
                        } while (compare_operator_priority(*p) < 0);
                        push(*p);
                    }
                }
                p++;
            }
        }
        while (top != NULL) {
            postfix[idx++] = pop();
        }
        postfix[idx] = '\0';
        double ans = eval_postfix(postfix);
        printf("%.15lf\n", ans);
    }
    return 0;
}