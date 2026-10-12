/*
 * Experiment 18: Turing Machine that accepts strings of the form ww
 *                w is any string over {a,b}.  e.g. abab, aa, abbabb
 *
 * Tape: '_' is the blank symbol. Input is written from cell 1.
 *
 * PHASE 1 - find the middle (states q0..q3):
 *   Mark symbols alternately from the left and from the right
 *   (a -> A, b -> B). When q0 meets a marked symbol we are at the
 *   start of the second half. If the length is odd -> reject.
 *   q0: a -> A,R,q1   b -> B,R,q1   A/B -> (no move) q4   _ -> accept
 *   q1: a,b -> R      A,B,_ -> L, q2
 *   q2: a -> A,L,q3   b -> B,L,q3   (anything else -> reject, odd length)
 *   q3: a,b -> L      A,B -> R, q0
 *
 * PHASE 2 - turn the second half back to lowercase (q4, q5):
 *   q4: A -> a,R   B -> b,R   _ -> L, q5
 *   q5: move L until _ , then R, q6
 *
 * PHASE 3 - compare first half (A/B) with second half (a/b):
 *   q6: A -> X,R,q7   B -> X,R,q8   Y -> accept
 *   q7: skip A,B,Y right;  a -> Y,L,q9   (else reject)
 *   q8: skip A,B,Y right;  b -> Y,L,q9   (else reject)
 *   q9: move L until X, then R, q6
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

        /* ---------- Phase 1: find the middle ---------- */
        if (state == 0) {
            if (c == 'a')                { tape[head] = 'A'; head++; state = 1; }
            else if (c == 'b')           { tape[head] = 'B'; head++; state = 1; }
            else if (c == 'A' || c == 'B') state = 4;        /* middle found */
            else if (c == '_')           { accept = 1; break; } /* empty string */
            else break;
        }
        else if (state == 1) {
            if (c == 'a' || c == 'b') head++;
            else { head--; state = 2; }                    /* A, B or _ */
        }
        else if (state == 2) {
            if (c == 'a')      { tape[head] = 'A'; head--; state = 3; }
            else if (c == 'b') { tape[head] = 'B'; head--; state = 3; }
            else break;                                    /* odd length */
        }
        else if (state == 3) {
            if (c == 'a' || c == 'b') head--;
            else { head++; state = 0; }                    /* hit A or B */
        }

        /* ---------- Phase 2: second half to lowercase ---------- */
        else if (state == 4) {
            if (c == 'A')      { tape[head] = 'a'; head++; }
            else if (c == 'B') { tape[head] = 'b'; head++; }
            else               { head--; state = 5; }      /* reached _ */
        }
        else if (state == 5) {
            if (c != '_') head--;
            else { head++; state = 6; }
        }

        /* ---------- Phase 3: compare the two halves ---------- */
        else if (state == 6) {
            if (c == 'A')      { tape[head] = 'X'; head++; state = 7; }
            else if (c == 'B') { tape[head] = 'X'; head++; state = 8; }
            else if (c == 'Y') { accept = 1; break; }      /* all matched */
            else break;
        }
        else if (state == 7 || state == 8) {
            char need = (state == 7) ? 'a' : 'b';
            if (c == 'A' || c == 'B' || c == 'Y') head++;
            else if (c == need) { tape[head] = 'Y'; head--; state = 9; }
            else break;                                    /* mismatch */
        }
        else if (state == 9) {
            if (c != 'X') head--;
            else { head++; state = 6; }
        }
    }

    if (accept) printf("String is of the form ww -> ACCEPTED by the TM\n");
    else        printf("String is not of the form ww -> REJECTED by the TM\n");
    return 0;
}
