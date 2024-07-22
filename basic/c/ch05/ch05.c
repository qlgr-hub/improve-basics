#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 100

static char buf[BUFSIZE];
static int  bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch()))
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    
    if (c != EOF)
        ungetch(c);
    
    return c;
}

#define SIZE 60

int main1()
{
    int n, array[SIZE], getint(int *);

    for (n = 0; n < SIZE; ++n)
        array[n] = 0;

    for (n = 0; n < SIZE && getint(&array[n]) != EOF; ++n)
        ;

    for (n = 0; n < SIZE; ++n)
        printf("%10d ", array[n]);
    printf("\n");

    return 0;
}


int strlen1(char *s)
{
    int n;

    for (n = 0; *s != '\0'; s++)
        n++;

    return n;
}

int strlen2(char *s)
{
    char *p = s;

    while (*p != '\0')
        p++;
    return p - s;
}

void strcpy1(char *s, char *t)
{
    int i;

    i = 0;
    while ( (s[i] = t[i]) != '\0' ) 
        i++;
}

void strcpy2(char *s, char *t)
{
    while ( (*s = *t) != '\0' ) {
        s++;
        t++;
    }
}

void strcpy3(char *s, char *t)
{
    while ( (*s++ = *t++) != '\0' )
        ;
}

void strcpy4(char *s, char *t)
{
    while (*s++ = *t++)
        ;
}

int strcmp1(char *s, char *t)
{
    int i;

    for (i = 0; s[i] == t[i]; i++)
        if (s[i] == '\0')
            return 0;
    return s[i] - t[i];
}

int strcmp2(char *s, char *t)
{
    for ( ; *s == *t; s++, t++)
        if (*s == '\0')
            return 0;
    return *s - *t;
}

int main2()
{
    char array[100];
    strcpy4(array, "hello aaaa");
    char *ptr = &array[3];

    printf("%d\n", strlen1("hello world"));
    printf("%d\n", strlen1(array));
    printf("%d\n", strlen1(ptr));

    printf("%d\n", strlen2("hello world"));
    printf("%d\n", strlen2(array));
    printf("%d\n", strlen2(ptr));

    return 0;
}


#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else 
        return 0;
}

void afree(char *p)
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}


#define MAXLINES 5000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort1(char *lineptr[], int left, int right);

int main3()
{
    int nlines;

    if ( (nlines = readlines(lineptr, MAXLINES)) >= 0 ) {
        qsort1(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

int getline1(char s[], int lim) 
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';
    return i;
}

#define MAXLEN 1000

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ( (len = getline1(line, MAXLEN)) > 0 )
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

void writelines1(char *lineptr[], int nlines)
{
    int i;

    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

void swap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void qsort1(char *v[], int left, int right)
{
    int i, last;
    
    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left+1; i <= right; ++i)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort1(v, left, last - 1);
    qsort1(v, last + 1, right);
}



int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);

    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

void swap1(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void qsort2(void *v[], int left, int right, int (*comp)(void *, void *))
{
    int i, last;
    
    if (left >= right)
        return;

    swap1(v, left, (left + right) / 2);
    last = left;
    for (i = left+1; i <= right; ++i)
        if ((*comp)(v[i], v[left]) < 0)
            swap1(v, ++last, i);
    swap1(v, left, last);
    qsort2(v, left, last - 1, comp);
    qsort2(v, last + 1, right, comp);
}

int main(int argc, char *argv[])
{
    int nlines;
    int numeric = 0;

    if (argc > 1 && strcmp(argv[1], "-n") == 0)
        numeric = 1;

    if ( (nlines = readlines(lineptr, MAXLINES)) >= 0 ) {
        qsort2((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))(numeric ? numcmp : strcmp));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day)
{
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}

char *month_name(int n)
{
    static char *name[] = {
        "Illegal month",
        "January", "February", "March",
        "April", "May", "June",
        "July", "August", "September",
        "October", "November", "December"
    };

    return (n < 1 || n > 12) ? name[0] : name[n];
}

int main4()
{
    int yearday, month, day;

    yearday = day_of_year(2021, 11, 7);
    printf("yearday = %d\n", yearday);

    month_day(2021, yearday, &month, &day);
    printf("month = %s, day = %d\n", month_name(month), day);

    return 0;
}


int main5(int argc, char *argv[])
{
    int i;

    for (i = 1; i < argc; i++)
        printf("%s%s", argv[i], (i < argc - 1) ? " " : "");
    printf("\n");
    return 0;
}

int main6(int argc, char *argv[])
{
    while (--argc > 0)
        printf("%s%s", *++argv, (argc > 1) ? " " : "");
    printf("\n");
    return 0;
}

int main7(int argc, char *argv[])
{
    while (--argc > 0)
        printf((argc > 1) ? "%s " : "%s", *++argv);
    printf("\n");
    return 0;
}

int main8(int argc, char *argv[])
{
    char line[MAXLEN];
    int found = 0;

    if (argc != 2)
        printf("usage: ./a.out pattern\n");
    else
        while (getline1(line, MAXLEN) > 0)
            if (strstr(line, argv[1]) != NULL) {
                printf("%s", line);
                found++;
            }

    return found;
}

int main9(int argc, char *argv[])
{
    char line[MAXLEN];
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;

    while (--argc > 0 && (*++argv)[0] == '-')
        while (c = *++argv[0])
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
                    printf("find: illegal option %c\n", c);
                    argc = 0;
                    found = -1;
                    break;
            }

    if (argc != 1)
        printf("usage: ./a.out -x -n pattern\n");
    else
        while (getline1(line, MAXLEN) > 0) {
            lineno++;
            if ( (strstr(line, *argv) != NULL) != except ) {
                if (number)
                    printf("%ld: ", lineno);
                printf("%s", line);
                found++;
            }
        }
    return found;
}