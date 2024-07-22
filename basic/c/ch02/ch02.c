#include <stdio.h>

int strlen1(char s[])
{
    int i;

    i = 0;
    while (s[i] != '\0')
        ++i;
    return i;
}

void checkleapyear(int year)
{
    if ( (year % 4 == 0 && year % 100 != 0) || year % 400 == 0 )
        printf("%d is a leap year\n", year);
    else 
        printf("%d is not a leap year\n", year);
}

int atoi(char s[])
{
    int i, n;

    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = 10 * n + (s[i] - '0');
    return n;
}

int lower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 'a' - 'A';
    else 
        return c;
}

unsigned long int next = 1;

int rand(void)
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next/65536) % 32768;
}

void srand(unsigned int seed)
{
    next = seed;
}

void squeeze(char s[], int c)
{
    int i, j;

    for (i = j = 0; s[i] != '\0'; ++i)
        if (s[i] != c)
            s[j++] = s[i];

    s[j] = '\0';
}

void strcat1(char s[], char t[])
{
    int i, j;

    i = j = 0;
    while (s[i] != '\0')
        i++;
    while ( (s[i++] = t[j++]) != '\0' )
        ;
}

int bitcount(unsigned x)
{
    int b;

    for (b = 0; x != 0; x >>= 1)
        if (x & 01)
            b++;
    return b;
}

int main()
{
    int i;
    char s[] = "dawdaDWADAWDDddwda456456";
    char t[256];

    printf("%o %d %x\n", '\013', '\013', '\013');
    printf("%o %d %x\n", '\xb', '\xb', '\xb');

    printf("%d\n", strlen1("dawdawdw"));

    checkleapyear(2000);

    printf("%d\n", atoi("1213dawdawd"));

    printf("%s\n", s);
    for (i = 0; i < strlen1(s); ++i)
        s[i] = lower(s[i]);
    printf("%s\n", s);

    // for (i = 0; i < 100; ++i) {
    //     printf("%d\n", rand());
    // }

    srand(100);
    for (i = 0; i < 100; ++i) {
        printf("%d\n", rand());
    }

    squeeze(s, 'd');
    printf("%s\n", s);

    for (i = 0; i < 256; i++) {
        t[i] = 0;
    }

    for (i = 0; i < 10; i++) {
        t[i] = 'A' + i;
    }

    strcat1(t, s);
    printf("%s\n", t);

    printf("%d\n", bitcount(255));
    return 0;
}