/*
 * Experiment 17: Turing Machine that accepts palindromes (test string: ababa)
 *
 * Language: palindromes over {a,b}   e.g. a, aba, ababa, bbabb, abba
 *
 * Tape: '_' is the blank symbol. Input is written from cell 1.
 *
 * Idea: erase the first symbol and remember it (q1 for a, q2 for b),
 *       run to the right end and check that the last symbol matches,
 *       erase it, go back to the left end and repeat.
 *
 * Transitions  (state, read) -> (write, move, next state):
 *   q0: a -> _, R, q1     b -> _, R, q2     _ -> accept
 *   q1: a,b -> R, q1      _ -> _, L, q3
 *   q3: a -> _, L, q5     _ -> accept       (b -> reject)
 *   q2: a,b -> R, q2      _ -> _, L, q4
 *   q4: b -> _, L, q5     _ -> accept       (a -> reject)
 *   q5: a,b -> L, q5      _ -> _, R, q0
 */
#include <stdio.h>

int main() {
    char tape[200], str[100];
    int i, head = 1, state = 0, accept = 0;

    printf("Enter the input string: ");
    scanf("%s", str);

    for (i = 0; i < 200; i++) tape[i] = '_';
    for (i = 0; str[i] != '\0'; i++) tape[i + 1] = str[i];

    while (1) {
        char c = tape[head];

        if (state == 0) {                       /* read & erase leftmost */
            if (c == 'a')      { tape[head] = '_'; head++; state = 1; }
            else if (c == 'b') { tape[head] = '_'; head++; state = 2; }
            else if (c == '_') { accept = 1; break; }
            else break;
        }
        else if (state == 1 || state == 2) {    /* go to right end */
            if (c == 'a' || c == 'b') head++;
            else if (c == '_') { head--; state = state + 2; }
            else break;
        }
        else if (state == 3) {                  /* rightmost must be a */
            if (c == 'a')      { tape[head] = '_'; head--; state = 5; }
            else if (c == '_') { accept = 1; break; }
            else break;
        }
        else if (state == 4) {                  /* rightmost must be b */
            if (c == 'b')      { tape[head] = '_'; head--; state = 5; }
            else if (c == '_') { accept = 1; break; }
            else break;
        }
        else if (state == 5) {                  /* go back to left end */
            if (c == 'a' || c == 'b') head--;
            else if (c == '_') { head++; state = 0; }
            else break;
        }
    }

    if (accept) printf("%s is a palindrome -> ACCEPTED by the TM\n", str);
    else        printf("%s is not a palindrome -> REJECTED by the TM\n", str);
    return 0;
}
