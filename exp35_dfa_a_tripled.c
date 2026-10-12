/*
 * Experiment 35: DFA for strings in which a's always appear TRIPLED
 * Alphabet: {a,b}
 * Language = (b + aaa)*   e.g. aaa, baaab, aaabaaa, aaaaaa
 *
 * States:
 *   q0 - start, a's are complete groups of three (FINAL)
 *   q1 - read one a of a group
 *   q2 - read two a's of a group
 *   q3 - dead state (a group of a's was broken by b)
 *
 * Transition table:
 *           a    b
 *   q0   q1   q0 
 *   q1   q2   q3 
 *   q2   q0   q3 
 *   q3   q3   q3 
 */
#include <stdio.h>

#define N 4   /* number of states  */
#define S 2   /* number of symbols */

int main() {
    /* dfa[state][symbol] gives the next state.
       Symbol index: 'a' -> 0, next letter -> 1, ... */
    int dfa[N][S] = {
        {1, 0}   /* q0 */,
        {2, 3}   /* q1 */,
        {0, 3}   /* q2 */,
        {3, 3}   /* q3 */
    };
    int final[N] = {1, 0, 0, 0};   /* 1 = final (accepting) state */
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
