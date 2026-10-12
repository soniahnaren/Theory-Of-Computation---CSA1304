/*
 * Experiment 2: DFA for strings that START with '0' and END with '1'
 * Alphabet: {0, 1}
 *
 * States:
 *   q0 - start state
 *   q1 - started with 0, last symbol is 0
 *   q2 - started with 0, last symbol is 1   (FINAL)
 *   q3 - dead state (string started with 1)
 *
 * Transition table:
 *          0    1
 *   q0    q1   q3
 *   q1    q1   q2
 *   q2    q1   q2
 *   q3    q3   q3
 */
#include <stdio.h>

int main() {
    /* dfa[state][symbol]  -> symbol 0 = '0', symbol 1 = '1' */
    int dfa[4][2] = {
        {1, 3},   /* q0 */
        {1, 2},   /* q1 */
        {1, 2},   /* q2 */
        {3, 3}    /* q3 (dead) */
    };
    char str[100];
    int i, sym, state = 0;

    printf("Enter a binary string: ");
    scanf("%s", str);

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != '0' && str[i] != '1') {
            printf("Invalid symbol '%c'\n", str[i]);
            return 0;
        }
        sym = str[i] - '0';          /* '0' -> 0, '1' -> 1 */

        printf("q%d --%c--> q%d\n", state, str[i], dfa[state][sym]);
        state = dfa[state][sym];
    }

    if (state == 2) printf("String is ACCEPTED\n");
    else            printf("String is REJECTED\n");
    return 0;
}
