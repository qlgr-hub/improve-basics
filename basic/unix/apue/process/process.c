#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static void  f1(int, int, int, int);
static void  f2(void);


static jmp_buf jmpbuffer;
static int     globval;

int main(void)
{
    int          autoval;
    register int regival;
    volatile int volaval;
    static   int statval;

    globval = 1; autoval = 2; regival = 3; volaval = 4; statval = 5;

    if (setjmp(jmpbuffer) != 0) {
        printf("after longjmp:\n");
        printf("globval = %d autoval = %d regival = %d volaval = %d statval = %d\n",
            globval, autoval, regival, volaval, statval);

        exit(0);
    }


    /*
     * Change variables after setjmp, but before longjmp.
     */
    globval = 95; autoval = 96; regival = 97; volaval = 98; statval = 99;

    f1(autoval, regival, volaval, statval); /* never returns */
    exit(0);
}

static void f1(int i, int j, int k, int l)
{
    printf("in f1():\n");
    printf("globval = %d autoval = %d regival = %d volaval = %d statval = %d\n",
        globval, i, j, k, l);

    f2();
}

static void f2(void)
{
    longjmp(jmpbuffer, 1);
}




















// extern char **environ;

// int main(int argc, char *argv[])
// {
//     int i;

//     //for (i = 0; i < argc; i++)
//     for (i = 0; argv[i] != NULL; i++)
//         printf("argv[%d]: %s\n", i, argv[i]);


//     for (i = 0; environ[i] != NULL; i++)
//         printf("environ[%d]: %s\n", i, environ[i]);

//     printf("environ[PATH]: %s\n", getenv("PATH"));

//     exit(0);
// }
















// static void my_exit1(void);
// static void my_exit2(void);

// int main()
// {
//     if (atexit(my_exit2) != 0) {
//         printf("can't register my_exit2");
//         exit(1);
//     }

//     if (atexit(my_exit1) != 0) {
//         printf("can't register my_exit1 1");
//         exit(1);
//     }

//     if (atexit(my_exit1) != 0) {
//         printf("can't register my_exit1 2");
//         exit(1);
//     }

//     printf("main is done\n");
//     return (0);
// }

// static void my_exit1(void)
// {
//     printf("first exit handler\n");
// }

// static void my_exit2(void)
// {
//     printf("second exit handler\n");
// }