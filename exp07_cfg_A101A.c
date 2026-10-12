/*
 * Experiment 7: Check whether a string belongs to the language of the CFG
 *      S -> A101A
 *      A -> 0A | 1A | e
 *
 * Meaning: A generates any string of 0s and 1s.
 * So S generates every binary string that CONTAINS "101" as a substring.
 * (e.g. 101, 0101, 11010, 0001011)
 */
#include <stdio.h>
#include <string.h>

char str[100];

/* A -> 0A | 1A | e : str[i..j] contains only 0s and 1s */
int A(int i, int j) {
    if (i > j) return 1;
    if (str[i] == '0' || str[i] == '1') return A(i + 1, j);
    return 0;
}

/* S -> A101A : try every position k where "101" could start */
int S(int n) {
    int k;
    for (k = 0; k + 2 < n; k++) {
        if (str[k] == '1' && str[k + 1] == '0' && str[k + 2] == '1')
            if (A(0, k - 1) && A(k + 3, n - 1))   /* left A and right A */
                return 1;
    }
    return 0;
}

int main() {
    printf("Enter a string: ");
    scanf("%s", str);

    if (S(strlen(str)))
        printf("String is ACCEPTED by the grammar\n");
    else
        printf("String is REJECTED by the grammar\n");
    return 0;
}
