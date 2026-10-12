/*
 * Experiment 4: Check whether a string belongs to the language of the CFG
 *      S -> 0S0 | 1S1 | 0 | 1 | e
 *
 * Meaning: the grammar generates all PALINDROMES over {0,1}.
 * (e.g. 0, 1, 00, 101, 0110, 10101)
 *
 * The function S(i, j) checks whether str[i..j] can be derived from S.
 */
#include <stdio.h>
#include <string.h>

char str[100];

int S(int i, int j) {
    if (i > j) return 1;                               /* S -> e        */
    if (i == j)                                        /* S -> 0 | 1    */
        return (str[i] == '0' || str[i] == '1');
    if (str[i] == '0' && str[j] == '0')                /* S -> 0S0      */
        return S(i + 1, j - 1);
    if (str[i] == '1' && str[j] == '1')                /* S -> 1S1      */
        return S(i + 1, j - 1);
    return 0;                                          /* no rule fits  */
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
