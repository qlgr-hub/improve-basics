#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

#define MAXLINE 1000

int getline1(char line[], int max);
int strindex(char source[], char seachfor[]);

char pattern[] = "ould";

void printd(int n)
{
    if (n < 0) {
        putchar('-');
        n = -n;
    }

    if (n / 10)
        printd(n / 10);
    putchar(n % 10 + '0');
}

int main1()
{
    char line[MAXLINE];
    int found = 0;
    
    while (getline1(line, MAXLINE) > 0) 
        if (strindex(line, pattern) >= 0) {
            printf("%s\n", line);
            found++;
        }
    return found;
}

int main2()
{
    double sum, atof1(char[]);
    char line[MAXLINE];
    int getline1(char line[], int max);
    
    sum = 0;
    while (getline1(line, MAXLINE) > 0)
        printf("\t%g\n", sum += atof1(line));
    return 0;
}

int main3()
{
    int n = 23497;
    printd(n);
    return 0;
}

int main()
{
    clock_t start, end;
    double total;
    int i, v[1000000];
    void qsort1(int v[], int left, int right);

    srand(time(NULL));
    for (i = 0; i < 1000000; ++i)
        v[i] = rand() % 1000000;

    for (i = 0; i < 1000000; ++i)
        printf("%8d ", v[i]);
    printf("\n");

    start = clock();
    qsort1(v, 0, 1000000 - 1);
    end = clock();
    total = (double)(end - start) / CLOCKS_PER_SEC;
    printf("1000000 element qsort1 use %g second.\n", total);

    for (i = 0; i < 1000000; ++i)
        printf("%8d ", v[i]);
    printf("\n");

    return 0;
}

int getline1(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

int strindex(char s[], char t[])
{
    int i, j, k;

    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}

double atof1(char s[])
{
    double val, power;
    int i, sign;

    for (i = 0; isspace(s[i]); ++i)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        ++i;
    for (val = 0.0; isdigit(s[i]); ++i)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        ++i;
    for (power = 1.0; isdigit(s[i]); ++i) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    return sign * val / power;
}

void swap(int v[], int i, int j)
{
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void qsort1(int v[], int left, int right)
{
    int i, last;
    
    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left+1; i <= right; ++i)
        if (v[i] < v[left])
            swap(v, ++last, i);
    swap(v, left, last);
    qsort1(v, left, last - 1);
    qsort1(v, last + 1, right);
}