/*
 * Experiment 12: DFA that accepts only the strings "a", "ac" and "bac"
 * Alphabet: {a,b,c}
 *
 * States:
 *   q0 - start
 *   q1 - read "a"   (FINAL)
 *   q2 - read "ac"  (FINAL)
 *   q3 - read "b"
 *   q4 - read "ba"
 *   q5 - read "bac" (FINAL)
 *   q6 - dead state
 *
 * Transition table:
 *           a    b    c
 *   q0   q1   q3   q6 
 *   q1   q6   q6   q2 
 *   q2   q6   q6   q6 
 *   q3   q4   q6   q6 
 *   q4   q6   q6   q5 
 *   q5   q6   q6   q6 
 *   q6   q6   q6   q6 
 */
#include <stdio.h>

#define N 7   /* number of states  */
#define S 3   /* number of symbols */

int main() {
    /* dfa[state][symbol] gives the next state.
       Symbol index: 'a' -> 0, next letter -> 1, ... */
    int dfa[N][S] = {
        {1, 3, 6}   /* q0 */,
        {6, 6, 2}   /* q1 */,
        {6, 6, 6}   /* q2 */,
        {4, 6, 6}   /* q3 */,
        {6, 6, 5}   /* q4 */,
        {6, 6, 6}   /* q5 */,
        {6, 6, 6}   /* q6 */
    };
    int final[N] = {0, 1, 1, 0, 0, 1, 0};   /* 1 = final (accepting) state */
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
