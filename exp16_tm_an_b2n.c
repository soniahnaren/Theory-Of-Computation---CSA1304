/*
 * Experiment 16: Turing Machine that accepts a^n b^2n  (n >= 1)
 *                e.g. abb, aabbbb
 *
 * Tape: '_' is the blank symbol. Input is written from cell 1.
 *
 * Idea: replace one 'a' by X, then TWO b's by Y, go back and repeat.
 *
 * Transitions  (state, read) -> (write, move, next state):
 *   q0: a -> X, R, q1     Y -> Y, R, q3
 *   q1: a -> a, R, q1     Y -> Y, R, q1     b -> Y, R, q4
 *   q4: b -> Y, L, q2                       (second b)
 *   q2: a -> a, L, q2     Y -> Y, L, q2     X -> X, R, q0
 *   q3: Y -> Y, R, q3     _ -> _, accept
 *   any other combination -> reject
 */
#include <stdio.h>
#include <string.h>

int main() {
    char tape[200], str[100];
    int i, head = 1, state = 0, accept = 0;

    printf("Enter the input string: ");
    scanf("%s", str);

    for (i = 0; i < 200; i++) tape[i] = '_';
    for (i = 0; str[i] != '\0'; i++) tape[i + 1] = str[i];

    while (1) {
        char c = tape[head];

        if (state == 0) {
            if (c == 'a')      { tape[head] = 'X'; head++; state = 1; }
            else if (c == 'Y') { head++; state = 3; }
            else break;
        }
        else if (state == 1) {
            if (c == 'a' || c == 'Y') head++;
            else if (c == 'b') { tape[head] = 'Y'; head++; state = 4; }
            else break;
        }
        else if (state == 4) {
            if (c == 'b') { tape[head] = 'Y'; head--; state = 2; }
            else break;
        }
        else if (state == 2) {
            if (c == 'a' || c == 'Y') head--;
            else if (c == 'X') { head++; state = 0; }
            else break;
        }
        else if (state == 3) {
            if (c == 'Y') head++;
            else if (c == '_') { accept = 1; break; }
            else break;
        }
    }

    tape[strlen(str) + 1] = '\0';
    printf("Final tape: %s\n", tape + 1);
    if (accept) printf("String is ACCEPTED by the TM\n");
    else        printf("String is REJECTED by the TM\n");
    return 0;
}
