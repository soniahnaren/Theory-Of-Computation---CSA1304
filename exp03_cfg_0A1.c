/*
 * Experiment 3: Check whether a string belongs to the language of the CFG
 *      S -> 0A1
 *      A -> 0A | 1A | e      (e = epsilon / empty string)
 *
 * Meaning: A produces ANY string of 0s and 1s.
 * So S produces strings that start with 0, end with 1 and
 * contain only 0s and 1s in between.  (e.g. 01, 001, 0101, 0111)
 *
 * Each grammar rule is written as a function working on str[i..j].
 * An empty range (i > j) means the empty string e.
 */
#include <stdio.h>
#include <string.h>

char str[100];

/* A -> 0A | 1A | e  : every symbol in str[i..j] must be 0 or 1 */
int A(int i, int j) {
    if (i > j) return 1;                         /* A -> e  */
    if (str[i] == '0' || str[i] == '1')          /* A -> 0A or A -> 1A */
        return A(i + 1, j);
    return 0;
}

/* S -> 0A1 : first symbol 0, last symbol 1, middle derived from A */
int S(int i, int j) {
    if (j - i + 1 < 2) return 0;                 /* need at least "01" */
    if (str[i] == '0' && str[j] == '1')
        return A(i + 1, j - 1);
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
