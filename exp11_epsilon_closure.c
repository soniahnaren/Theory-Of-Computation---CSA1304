/*
 * Experiment 11: Find the e-closure of every state of an NFA with e-moves
 *
 * This version reads the COMPLETE NFA (all transitions), keeps only the
 * e-transitions and uses a STACK (no recursion) to find the closures.
 *
 * Input format for each transition:  from symbol to
 *   use the symbol 'e' for an epsilon move
 *
 * Sample input:
 *   Number of states: 4
 *   Number of transitions: 5
 *   0 e 1
 *   0 a 2
 *   1 e 2
 *   2 b 3
 *   3 e 0
 * Output:
 *   e-closure(q0) = {q0, q1, q2}
 *   e-closure(q1) = {q1, q2}
 *   e-closure(q2) = {q2}
 *   e-closure(q3) = {q0, q1, q2, q3}
 */
#include <stdio.h>

#define MAX 20

int main() {
    int eps[MAX][MAX] = {0};   /* eps[p][q] = 1 means p --e--> q */
    int inClosure[MAX];
    int stack[MAX], top;
    int n, m, i, p, q, first;
    char sym;

    printf("Enter number of states: ");
    scanf("%d", &n);
    printf("Enter number of transitions: ");
    scanf("%d", &m);
    printf("Enter each transition as: from symbol to  (use e for epsilon)\n");
    for (i = 0; i < m; i++) {
        scanf("%d %c %d", &p, &sym, &q);
        if (sym == 'e') eps[p][q] = 1;     /* keep only e-moves */
    }

    for (p = 0; p < n; p++) {
        /* start with the state itself */
        for (q = 0; q < n; q++) inClosure[q] = 0;
        top = -1;
        stack[++top] = p;
        inClosure[p] = 1;

        /* pop a state, push all its unvisited e-neighbours */
        while (top >= 0) {
            int s = stack[top--];
            for (q = 0; q < n; q++)
                if (eps[s][q] && !inClosure[q]) {
                    inClosure[q] = 1;
                    stack[++top] = q;
                }
        }

        printf("e-closure(q%d) = {", p);
        first = 1;
        for (q = 0; q < n; q++)
            if (inClosure[q]) {
                printf(first ? "q%d" : ", q%d", q);
                first = 0;
            }
        printf("}\n");
    }
    return 0;
}
