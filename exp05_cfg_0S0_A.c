/*
 * Experiment 5: Check whether a string belongs to the language of the CFG
 *      S -> 0S0 | A
 *      A -> 1A | e
 *
 * Meaning: A generates any number of 1s (1^m).
 * S wraps that with an equal number of 0s on both sides.
 * Language = { 0^n 1^m 0^n  |  n >= 0, m >= 0 }
 * (e.g. 1, 010, 00100, 0110, 00, 0000)
 */
#include <stdio.h>
#include <string.h>

char str[100];

/* A -> 1A | e : str[i..j] must contain only 1s */
int A(int i, int j) {
    if (i > j) return 1;                  /* A -> e  */
    if (str[i] == '1') return A(i + 1, j);/* A -> 1A */
    return 0;
}

/* S -> 0S0 | A */
int S(int i, int j) {
    if (i < j && str[i] == '0' && str[j] == '0')   /* try S -> 0S0 */
        return S(i + 1, j - 1);
    return A(i, j);                                /* else S -> A  */
}

int main() {
    printf("Enter a string: ");
    scanf("%s", str);

    if (S(0, strlen(str) - 1))
        printf("String is ACCEPTED by the grammar\n");
    else
        printf("String is REJECTED by the grammar\n");
    return 0;
}
