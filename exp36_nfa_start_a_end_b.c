/*
 * Experiment 36: NFA for strings that START with 'a' and END with 'b'
 * Alphabet: {a,b}
 * Test string W = abaab  (expected: ACCEPTED)
 *
 * States:
 *   q0 - start state
 *   q1 - first symbol was a (loops on a,b)
 *   q2 - final state (guessed last symbol b)
 *
 * Transitions (an NFA may go to MORE THAN ONE state, or to NONE):
 *   d(q0, a) = {q1}
 *   d(q1, a) = {q1}
 *   d(q1, b) = {q1, q2}
 *
 * Simulation idea: keep the SET of all states the NFA can be in.
 * For each input symbol, the new set = all states reachable from the
 * current set on that symbol. Accept if the final set has a final state.
 */
#include <stdio.h>

#define N 3   /* number of states  */
#define S 2   /* number of symbols */

int trans[N][S][N];   /* trans[p][x][q] = 1 means q is in d(p, x) */
int final[N] = {0, 0, 1};

/* print the current set of states, e.g. {q0, q1} */
void printSet(int set[]) {
    int q, first = 1;
    printf("{");
    for (q = 0; q < N; q++)
        if (set[q]) {
            printf(first ? "q%d" : ", q%d", q);
            first = 0;
        }
    printf("}\n");
}

int main() {
    char str[100];
    int cur[N] = {0}, next[N];
    int i, p, q, sym, accepted = 0;

    /* fill the transition table */
    trans[0][0][1] = 1;   /* q0 --a--> q1 */
    trans[1][0][1] = 1;   /* q1 --a--> q1 */
    trans[1][1][1] = 1;   /* q1 --b--> q1 */
    trans[1][1][2] = 1;   /* q1 --b--> q2 */

    printf("Enter a string over {a,b}: ");
    scanf("%s", str);

    cur[0] = 1;                       /* start in q0 */
    printf("Start : ");
    printSet(cur);

    for (i = 0; str[i] != '\0'; i++) {
        sym = str[i] - 'a';
        if (sym < 0 || sym >= S) {
            printf("Invalid symbol '%c'\n", str[i]);
            return 0;
        }

        /* compute the next set of states */
        for (q = 0; q < N; q++) next[q] = 0;
        for (p = 0; p < N; p++)
            if (cur[p])
                for (q = 0; q < N; q++)
                    if (trans[p][sym][q]) next[q] = 1;
        for (q = 0; q < N; q++) cur[q] = next[q];

        printf("On '%c': ", str[i]);
        printSet(cur);
    }

    /* accept if any reached state is final */
    for (q = 0; q < N; q++)
        if (cur[q] && final[q]) accepted = 1;

    if (accepted) printf("String is ACCEPTED\n");
    else          printf("String is REJECTED\n");
    return 0;
}
