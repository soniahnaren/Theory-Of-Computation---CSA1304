/*
 * Experiment 29: DFA that accepts only the strings "bc", "c" and "bcaaa"
 * Alphabet: {a,b,c}
 *
 * States:
 *   q0 - start
 *   q1 - read "b"
 *   q2 - read "c" (FINAL)
 *   q3 - read "bc" (FINAL)
 *   q4 - read "bca"
 *   q5 - read "bcaa"
 *   q6 - read "bcaaa" (FINAL)
 *   q7 - dead state
 *
 * Transition table:
 *           a    b    c
 *   q0   q7   q1   q2 
 *   q1   q7   q7   q3 
 *   q2   q7   q7   q7 
 *   q3   q4   q7   q7 
 *   q4   q5   q7   q7 
 *   q5   q6   q7   q7 
 *   q6   q7   q7   q7 
 *   q7   q7   q7   q7 
 */
#include <stdio.h>

#define N 8   /* number of states  */
#define S 3   /* number of symbols */

int main() {
    /* dfa[state][symbol] gives the next state.
       Symbol index: 'a' -> 0, next letter -> 1, ... */
    int dfa[N][S] = {
        {7, 1, 2}   /* q0 */,
        {7, 7, 3}   /* q1 */,
        {7, 7, 7}   /* q2 */,
        {4, 7, 7}   /* q3 */,
        {5, 7, 7}   /* q4 */,
        {6, 7, 7}   /* q5 */,
        {7, 7, 7}   /* q6 */,
        {7, 7, 7}   /* q7 */
    };
    int final[N] = {0, 0, 1, 1, 0, 0, 1, 0};   /* 1 = final (accepting) state */
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
