/*
 * Experiment 13: PDA that accepts the input string aabb (a^n b^n with n = 2)
 *
 * Language: { a^n b^n | n >= 1 }   e.g. ab, aabb, aaabbb
 *
 * PDA idea:
 *   q0 : for every 'a' PUSH one A onto the stack
 *   q1 : for every 'b' POP one A from the stack
 *   Accept when input is finished, we are in q1 and only Z (bottom) is left.
 *
 * Transitions:
 *   d(q0, a, Z) = (q0, AZ)     push A
 *   d(q0, a, A) = (q0, AA)     push A
 *   d(q0, b, A) = (q1, e)      pop A, switch to q1
 *   d(q1, b, A) = (q1, e)      pop A
 *   d(q1, e, Z) = (qf, Z)      accept
 */
#include <stdio.h>

char stack[100];
int top = -1;

void push(char c) { stack[++top] = c; }
void pop()        { top--; }

/* print stack contents from bottom to top */
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
            push('A');                           /* push for every a */
        } else if (str[i] == 'b' && stack[top] == 'A') {
            pop();                               /* pop for every b  */
            state = 1;
        } else {
            printf("\n   No valid move -> REJECTED\n");
            return 0;
        }
        showStack();
    }

    /* accept if we reached q1 and only Z is on the stack */
    if (state == 1 && stack[top] == 'Z')
        printf("String is ACCEPTED by the PDA\n");
    else
        printf("String is REJECTED by the PDA\n");
    return 0;
}
