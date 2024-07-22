#include "calc.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int main()
{
    int type;
    double op2;
    char s[MAXOP];

    while ( (type = getop(s)) != EOF ) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unkown command %s\n", s);
                break;

        }
    }
    return 0;
}
