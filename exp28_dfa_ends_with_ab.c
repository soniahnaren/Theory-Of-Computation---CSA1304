/*
 * Experiment 28: DFA that accepts strings ENDING with "ab"
 * Alphabet: {a,b}
 * Test string W = abbaabab  (expected: ACCEPTED)
 *
 * States:
 *   q0 - start / no useful suffix
 *   q1 - last symbol is a
 *   q2 - last two symbols are ab (FINAL)
 *
 * Transition table:
 *           a    b
 *   q0   q1   q0 
 *   q1   q1   q2 
 *   q2   q1   q0 
 */
#include <stdio.h>

#define N 3   /* number of states  */
#define S 2   /* number of symbols */

int main() {
    /* dfa[state][symbol] gives the next state.
       Symbol index: 'a' -> 0, next letter -> 1, ... */
    int dfa[N][S] = {
        {1, 0}   /* q0 */,
        {1, 2}   /* q1 */,
        {1, 0}   /* q2 */
    };
    int final[N] = {0, 0, 1};   /* 1 = final (accepting) state */
    char str[100];
    int i, sym, state = 0;       /* q0 is the start state */

    printf("Enter a string over {a,b}: ");
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
