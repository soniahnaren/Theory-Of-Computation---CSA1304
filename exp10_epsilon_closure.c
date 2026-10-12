/*
 * Experiment 10: Find the e-closure of every state of an NFA with e-moves
 *
 * e-closure(q) = the set of states reachable from q using ONLY
 *                e (epsilon) transitions, including q itself.
 *
 * Method: recursive Depth First Search (DFS) on the e-transitions.
 *
 * Sample input (states q0, q1, q2):
 *   Number of states: 3
 *   Number of e-transitions: 2
 *   0 1        (q0 --e--> q1)
 *   1 2        (q1 --e--> q2)
 * Output:
 *   e-closure(q0) = {q0, q1, q2}
 *   e-closure(q1) = {q1, q2}
 *   e-closure(q2) = {q2}
 */
#include <stdio.h>

#define MAX 20

int eps[MAX][MAX];      /* eps[p][q] = 1 means p --e--> q */
int visited[MAX];       /* states already put in the closure */
int n;                  /* number of states */

/* visit state p and every state reachable from it by e-moves */
void dfs(int p) {
    int q;
    visited[p] = 1;
    for (q = 0; q < n; q++)
        if (eps[p][q] && !visited[q])
            dfs(q);
}

int main() {
    int m, i, p, q, first;

    printf("Enter number of states: ");
    scanf("%d", &n);
    printf("Enter number of e-transitions: ");
    scanf("%d", &m);
    printf("Enter each e-transition as: from to  (e.g. 0 1)\n");
    for (i = 0; i < m; i++) {
        scanf("%d %d", &p, &q);
        eps[p][q] = 1;
    }

    /* compute closure for every state */
    for (p = 0; p < n; p++) {
        for (q = 0; q < n; q++) visited[q] = 0;   /* reset */
        dfs(p);

        printf("e-closure(q%d) = {", p);
        first = 1;
        for (q = 0; q < n; q++)
            if (visited[q]) {
                printf(first ? "q%d" : ", q%d", q);
                first = 0;
            }
        printf("}\n");
    }
    return 0;
}
