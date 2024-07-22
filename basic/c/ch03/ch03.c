#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

int search(int x, int v[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        if (v[i] == x)
            return i;
    return -1;
}

// 这个实现问题很大，+ -号出现在包含数字的字符串中任意位置都有可能被识别为符号
// 只忽略了前导的空白符没啥意义
// int atoi1(char s[])
// {
//     int i, n, sign;

//     for (i = 0; isspace(s[i]); ++i)
//         ;
//     sign = (s[i] == '-') ? -1 : 1;
//     if (s[i] == '+' || s[i] == '-')
//         i++;
//     for (n = 0; s[i] != '\0'; ++i)
//         if (isdigit(s[i]))
//             n = 10 * n + (s[i] - '0');
//     return sign * n;
// }

void shellsort(int v[], int n)
{
    int gap, i, j, temp;

    for (gap = n/2; gap > 0; gap /= 2)
        for (i = gap; i < n; ++i)
            for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap) {
                temp = v[j];
                v[j] = v[j + gap];
                v[j + gap] = temp;
            }
}

void bubblesort(int v[], int n)
{
    int i, j, temp;

    for (i = 0; i < n - 1; ++i)
        for (j = 0; j < n - 1 - i; ++j)
            if (v[j] > v[j + 1]) {
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
}

void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s) - 1; i < j; ++i, --j) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa1(int n, char s[])
{
    int i, sign;

    if ( (sign = n) < 0 )
        n = -n;

    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while( (n /= 10) > 0 );

    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';

    reverse(s);
}

int main()
{
    clock_t start, end;
    double total;
    int v[1000000], v1[1000000], i;
    char s[100];

    for (i = 0; i < 1000000; ++i)
    {
        v[i] = i;
    }

    for (i = 0; i < 100; ++i)
    {
        s[i] = 0;
    }
    
    start = clock();
    search(500, v, 1000000);
    end = clock();
    total = (double)(end - start) / CLOCKS_PER_SEC;
    printf("find 500 search need %f second\n", total);

    start = clock();
    binsearch(500, v, 1000000);
    end = clock();
    total = (double)(end - start) / CLOCKS_PER_SEC;
    printf("find 500 binsearch need %f second\n", total);

    start = clock();
    search(999999, v, 1000000);
    end = clock();
    total = (double)(end - start) / CLOCKS_PER_SEC;
    printf("find 999999 search need %f second\n", total);

    start = clock();
    binsearch(999999, v, 1000000);
    end = clock();
    total = (double)(end - start) / CLOCKS_PER_SEC;
    printf("find 999999 binsearch need %f second\n", total);

    //printf("%d %d\n", atoi1("dawdw12234"), atoi1(" dawd   -13133"));

    srand(time(NULL));
    for (i = 0; i < 1000000; ++i)
    {
        v[i] = rand() % 1000000;
        v1[i] = v[i];
    }

    for (i = 0; i < 1000000; ++i)
    {
        printf("%8d\t", v[i]);
    }
    printf("\n");

    start = clock();
    shellsort(v, 1000000);
    end = clock();
    total = (double)(end - start) / CLOCKS_PER_SEC;
    printf("1000000 element shellsort need %f second\n", total);

    for (i = 0; i < 1000000; ++i)
    {
        printf("%8d\t", v[i]);
    }
    printf("\n");

    for (i = 0; i < 1000000; ++i)
    {
        printf("%8d\t", v1[i]);
    }
    printf("\n");

    start = clock();
    bubblesort(v1, 1000000); //太慢，接受不了
    end = clock();
    total = (double)(end - start) / CLOCKS_PER_SEC;
    printf("1000000 element bubblesort need %f second\n", total);

    for (i = 0; i < 1000000; ++i)
    {
        printf("%8d\t", v1[i]);
    }
    printf("\n");

    itoa1(12312355, s);
    printf("%s\n", s);
    itoa1(-898975, s);
    printf("%s\n", s);

    return 0;
}



int main1()
{
    int c, i, nwhite, nother, ndigit[10];

    nwhite = nother = 0;
    for (i = 0; i < 10; ++i)
        ndigit[i] = 0;

    while ( (c = getchar()) != EOF ) {
        switch (c) {
            case '0': case '1': case '2': case '3': case '4': 
            case '5': case '6': case '7': case '8': case '9': 
                ++ndigit[c-'0'];
                break;

            case ' ': 
            case '\t': 
            case '\n':
                ++nwhite;
                break;
            default:
                ++nother;
                break; 
        }
    }

    printf("digits = ");
    for (i = 0; i < 10; ++i)
        printf(" %d", ndigit[i]);

    printf(", white space = %d, other = %d\n", nwhite, nother);

    return 0;
}


