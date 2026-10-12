/*
 * Experiment 6: Check whether a string belongs to the language of the CFG
 *      S -> 0S1 | e
 *
 * Meaning: Language = { 0^n 1^n | n >= 0 }
 * (e.g. 01, 0011, 000111)
 */
#include <stdio.h>
#include <string.h>

char str[100];

int S(int i, int j) {
    if (i > j) return 1;                           /* S -> e   */
    if (str[i] == '0' && str[j] == '1')            /* S -> 0S1 */
        return S(i + 1, j - 1);
    return 0;
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
