#include <stdio.h>

int getline1();
void copy();

int main()
{
    int len;
    extern int max;
    extern char longest[];
    
    max = 0;
    while ( (len = getline1()) > 0 ) {
        if (len > max) {
            max = len;
            copy();
        }
    }

    if (max > 0)
        printf("%s", longest);

    return 0;
}