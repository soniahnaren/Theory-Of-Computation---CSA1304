/*
 * Experiment 20: Turing Machine to perform SUBTRACTION of two unary numbers
 *                Example: aaa - aa  (3 - 2)  -> a  (1)
 *                (If the second number is bigger, the result is 0.)
 *
 * Input format on tape:  aaa-aa      ('_' = blank)
 *
 * Idea: repeatedly erase one 'a' from the RIGHT end of the second
 *       number and one 'a' from the LEFT end of the first number.
 *       When the second number is used up, erase '-' and halt.
 *
 * Transitions  (state, read) -> (write, move, next state):
 *   q0: a,- -> R, q0           _ -> _, L, q1    (go to right end)
 *   q1: a -> _, L, q2          - -> _, halt     (erase from 2nd number)
 *   q2: a,- -> L, q2           _ -> _, R, q3    (go to left end)
 *   q3: a -> _, R, q0          - -> _, R, q4    (erase from 1st number)
 *   q4: a -> _, R, q4          _ -> halt        (first ran out -> 0)
 */
#include <stdio.h>

int main() {
    char tape[200], str[100];
    int i, head = 1, state = 0, count = 0;

    printf("Enter the input (example aaa-aa): ");
    scanf("%s", str);

    for (i = 0; i < 200; i++) tape[i] = '_';
    for (i = 0; str[i] != '\0'; i++) tape[i + 1] = str[i];

    while (1) {
        char c = tape[head];

        if (state == 0) {
            if (c == 'a' || c == '-') head++;
            else { head--; state = 1; }
        }
        else if (state == 1) {
            if (c == 'a')      { tape[head] = '_'; head--; state = 2; }
            else if (c == '-') { tape[head] = '_'; break; }   /* halt */
            else break;
        }
        else if (state == 2) {
            if (c == 'a' || c == '-') head--;
            else { head++; state = 3; }
        }
        else if (state == 3) {
            if (c == 'a')      { tape[head] = '_'; head++; state = 0; }
            else if (c == '-') { tape[head] = '_'; head++; state = 4; }
            else break;
        }
        else if (state == 4) {
            if (c == 'a') { tape[head] = '_'; head++; }
            else break;                                       /* halt */
        }
    }

    /* count the a's left on the tape */
    printf("Result on tape: ");
    for (i = 1; i < 200; i++)
        if (tape[i] == 'a') { printf("a"); count++; }
    printf("   (value = %d)\n", count);
    return 0;
}
