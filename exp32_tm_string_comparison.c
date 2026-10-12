/*
 * Experiment 32: Turing Machine to perform STRING COMPARISON
 *                Input: two strings over {a,b} separated by a space,
 *                e.g. "aba aba" -> EQUAL,  "aba abb" -> NOT EQUAL
 *
 * Tape: '_' is the blank symbol. Input is written from cell 1.
 *
 * Idea: mark the first unmarked symbol of the left w with X, remember it,
 *       cross the separator ' ', find the first unmarked symbol of the
 *       right w, check it matches, mark it X, come back and repeat.
 *
 * Transitions  (state, read) -> (write, move, next state):
 *   q0: a -> X,R,q1    b -> X,R,q2    ' ' -> R,q5
 *   q1: a,b -> R       ' ' -> R,q3          (remembered a)
 *   q2: a,b -> R       ' ' -> R,q4          (remembered b)
 *   q3: X -> R         a -> X,L,q6          (else reject)
 *   q4: X -> R         b -> X,L,q6          (else reject)
 *   q6: X -> L         ' ' -> L,q7
 *   q7: a,b -> L       X -> R,q0
 *   q5: X -> R         _ -> accept          (else reject)
 */
#include <stdio.h>
#include <string.h>

#define SEP ' '     /* separator between the two strings */

int main() {
    char tape[200], str[100];
    int i, head = 1, state = 0, accept = 0;

    printf("Enter the input string (example aba aba): ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';       /* remove the newline */

    for (i = 0; i < 200; i++) tape[i] = '_';
    for (i = 0; str[i] != '\0'; i++) tape[i + 1] = str[i];

    while (1) {
        char c = tape[head];

        if (state == 0) {
            if (c == 'a')      { tape[head] = 'X'; head++; state = 1; }
            else if (c == 'b') { tape[head] = 'X'; head++; state = 2; }
            else if (c == SEP) { head++; state = 5; }
            else break;
        }
        else if (state == 1 || state == 2) {     /* move to separator */
            if (c == 'a' || c == 'b') head++;
            else if (c == SEP) { head++; state = state + 2; }
            else break;
        }
        else if (state == 3 || state == 4) {     /* match in right part */
            char need = (state == 3) ? 'a' : 'b';
            if (c == 'X') head++;
            else if (c == need) { tape[head] = 'X'; head--; state = 6; }
            else break;                          /* mismatch */
        }
        else if (state == 6) {                   /* back to separator */
            if (c == 'X') head--;
            else if (c == SEP) { head--; state = 7; }
            else break;
        }
        else if (state == 7) {                   /* back to last X on left */
            if (c == 'a' || c == 'b') head--;
            else if (c == 'X') { head++; state = 0; }
            else break;
        }
        else if (state == 5) {                   /* right part fully matched? */
            if (c == 'X') head++;
            else if (c == '_') { accept = 1; break; }
            else break;
        }
    }

    if (accept) printf("Both strings are EQUAL -> ACCEPTED by the TM\n");
    else        printf("Strings are NOT EQUAL -> REJECTED by the TM\n");
    return 0;
}
