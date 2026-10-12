/*
 * Experiment 34: DFA that accepts strings with an EVEN number of c's
 * Alphabet: {a,b,c}
 * a and b do not change the state; only c toggles it.
 *
 * States:
 *   q0 - even number of c's so far (start, FINAL)
 *   q1 - odd number of c's so far
 *
 * Transition table:
 *           a    b    c
 *   q0   q0   q0   q1 
 *   q1   q1   q1   q0 
 */
#include <stdio.h>

#define N 2   /* number of states  */
#define S 3   /* number of symbols */

int main() {
    /* dfa[state][symbol] gives the next state.
       Symbol index: 'a' -> 0, next letter -> 1, ... */
    int dfa[N][S] = {
        {0, 0, 1}   /* q0 */,
        {1, 1, 0}   /* q1 */
    };
    int final[N] = {1, 0};   /* 1 = final (accepting) state */
    char str[100];
    int i, sym, state = 0;       /* q0 is the start state */

    printf("Enter a string over {a,b,c}: ");
    scanf("%s", str);

    for (i = 0; str[i] != '\0'; i++) {
        sym = str[i] - 'a';            /* convert symbol to column number */
        if (sym < 0 || sym >= S) {
            printf("Invalid symbol '%c'\n", str[i]);
            return 0;
        }
        printf("q%d --%c--> q%d\n", state, str[i], dfa[state][sym]);
        state = dfa[state][sym];          /* move to the next state */
    }

    if (final[state]) printf("String is ACCEPTED\n");
    else              printf("String is REJECTED\n");
    return 0;
}
