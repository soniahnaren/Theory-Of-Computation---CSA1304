/*
 * Experiment 14: PDA that accepts strings of the form a^n b^2n
 *
 * Language: { a^n b^2n | n >= 1 }   e.g. abb, aabbbb, aaabbbbbb
 *
 * PDA idea:
 *   q0 : for every 'a' PUSH TWO A's onto the stack
 *   q1 : for every 'b' POP ONE A from the stack
 *   Accept when input is finished, we are in q1 and only Z is left.
 *
 * Transitions:
 *   d(q0, a, Z) = (q0, AAZ)    push two A
 *   d(q0, a, A) = (q0, AAA)    push two A
 *   d(q0, b, A) = (q1, e)      pop A, switch to q1
 *   d(q1, b, A) = (q1, e)      pop A
 *   d(q1, e, Z) = (qf, Z)      accept
 */
#include <stdio.h>

char stack[200];
int top = -1;

void push(char c) { stack[++top] = c; }
void pop()        { top--; }

void showStack() {
    int i;
    printf("   Stack: ");
    for (i = 0; i <= top; i++) printf("%c", stack[i]);
    printf("\n");
}

int main() {
    char str[100];
    int i, state = 0;

    printf("Enter the input string: ");
    scanf("%s", str);

    push('Z');                       /* bottom-of-stack marker */

    for (i = 0; str[i] != '\0'; i++) {
        printf("q%d reads '%c'", state, str[i]);

        if (state == 0 && str[i] == 'a') {
            push('A');                           /* two pushes per a */
            push('A');
        } else if (str[i] == 'b' && stack[top] == 'A') {
            pop();                               /* one pop per b    */
            state = 1;
        } else {
            printf("\n   No valid move -> REJECTED\n");
            return 0;
        }
        showStack();
    }

    if (state == 1 && stack[top] == 'Z')
        printf("String is ACCEPTED by the PDA\n");
    else
        printf("String is REJECTED by the PDA\n");
    return 0;
}
