/*
 * Experiment 19: Turing Machine to perform ADDITION of two unary numbers
 *                Example: aa + aaa  (2 + 3)  -> aaaaa  (5)
 *
 * Input format on tape:  aa+aaa      ('_' = blank)
 *
 * Idea: replace '+' by 'a' (this joins the numbers but adds one
 *       extra a), then go to the right end and erase the last 'a'.
 *
 * Transitions  (state, read) -> (write, move, next state):
 *   q0: a -> a, R, q0      + -> a, R, q1
 *   q1: a -> a, R, q1      _ -> _, L, q2
 *   q2: a -> _, halt
 */
#include <stdio.h>

int main() {
    char tape[200], str[100];
    int i, head = 1, state = 0, done = 0, count = 0;

    printf("Enter the input (example aa+aaa): ");
    scanf("%s", str);

    for (i = 0; i < 200; i++) tape[i] = '_';
    for (i = 0; str[i] != '\0'; i++) tape[i + 1] = str[i];

    while (1) {
        char c = tape[head];

        if (state == 0) {
            if (c == 'a') head++;
            else if (c == '+') { tape[head] = 'a'; head++; state = 1; }
            else break;                          /* no '+' : invalid */
        }
        else if (state == 1) {
            if (c == 'a') head++;
            else if (c == '_') { head--; state = 2; }
            else break;
        }
        else if (state == 2) {
            if (c == 'a') { tape[head] = '_'; done = 1; }
            break;                               /* halt */
        }
    }

    if (!done) {
        printf("Invalid input\n");
        return 0;
    }

    printf("Result on tape: ");
    for (i = 1; tape[i] == 'a'; i++) { printf("a"); count++; }
    printf("   (value = %d)\n", count);
    return 0;
}
