/*
 * Experiment 1: DFA for strings that START with 'a' and END with 'a'
 * Alphabet: {a, b}
 *
 * States:
 *   q0 - start state
 *   q1 - started with 'a', last symbol is 'a'   (FINAL)
 *   q2 - started with 'a', last symbol is 'b'
 *   q3 - dead state (string started with 'b')
 *
 * Transition table:
 *          a    b
 *   q0    q1   q3
 *   q1    q1   q2
 *   q2    q1   q2
 *   q3    q3   q3
 */
#include <stdio.h>

int main() {
    /* dfa[state][symbol]  -> symbol 0 = 'a', symbol 1 = 'b' */
    int dfa[4][2] = {
        {1, 3},   /* q0 */
        {1, 2},   /* q1 */
        {1, 2},   /* q2 */
        {3, 3}    /* q3 (dead) */
    };
    char str[100];
    int i, sym, state = 0;            /* begin in start state q0 */

    printf("Enter a string over {a,b}: ");
    scanf("%s", str);

    for (i = 0; str[i] != '\0'; i++) {
        /* convert the symbol into a column number */
        if (str[i] == 'a') sym = 0;
        else if (str[i] == 'b') sym = 1;
        else { printf("Invalid symbol '%c'\n", str[i]); return 0; }

        printf("q%d --%c--> q%d\n", state, str[i], dfa[state][sym]);
        state = dfa[state][sym];     /* move to next state */
    }

    /* q1 is the only final state */
    if (state == 1) printf("String is ACCEPTED\n");
    else            printf("String is REJECTED\n");
    return 0;
}
