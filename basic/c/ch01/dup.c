#include <stdio.h>

main()
{
    int c, i, nwhite, nother;
    int ndigit[10];

    nwhite = nother = 0;
    for (i = 0; i < 10; ++i)
        ndigit[i] = 0;

    while ( (c = getchar()) != EOF ) {
        if (c >= '0' && c <= '9')
            ++ndigit[c-'0'];
        else if (c == ' ' || c == '\n' || c == '\t')
            ++nwhite;
        else 
            ++nother;
    }
    printf("digits =");
    for (i = 0; i < 10; ++i)
        printf(" %d", ndigit[i]);
    printf(", white space = %d, other = %d\n", nwhite, nother);
}



// 1-12
//#define IN  1
//#define OUT 0
// main()
// {
//     int c, state;
//
//     state = OUT;
//     while ( (c = getchar()) != EOF ) {
//         if (c == ' ' || c == '\n' || c == '\t') {
//             if (state == IN) {
//                 putchar('\n');
//                 state = OUT;
//             }
//         }
//         else if (state == OUT) {
//             state = IN;
//             putchar(c);
//         }
//         else {
//             putchar(c);
//         }
//     }
// }




// #define IN  1
// #define OUT 0
// main()
// {
//     int c, nl, nw, nc, state;
//
//     state = OUT;
//     nl = nw = nc = 0;
//     while ( (c = getchar()) != EOF ) {
//         ++nc;
//         if (c == '\n')
//             ++nl;
//
//         if (c == ' ' || c == '\n' || c == '\t')
//             state = OUT;
//         else if (state == OUT) {
//             state = IN;
//             ++nw;
//         }
//     }
//     printf("%d %d %d\n", nl, nw, nc);
// }

// 1-10
// main()
// {
//     int c;
//
//     while ( (c = getchar()) != EOF ) {
//         switch (c)
//         {
//             case '\t': printf("\\t");  break;
//             case '\b': printf("\\b");  break;
//             case '\\': printf("\\\\"); break;
//             default  : putchar(c);     break;
//         }
//     }  
// }

// 1-9
// #define NONBLANK 'a'
// main()
// {
//     int c, lastc;
//
//     lastc = NONBLANK;
//     while ( (c = getchar()) != EOF ) {
//         if (c != ' ' || lastc != ' ')
//             putchar(c);
//
//         lastc = c;
//     }
// }


// 1-8
// main()
// {
//     int c, nb, nt, nl;
//
//     nb = 0, nt = 0, nl = 0;
//     while ( (c = getchar()) != EOF ) {
//         if (c == ' ')
//             ++nb;
//         if (c == '\t')
//             ++nt;
//         if (c == '\n')
//             ++nl;
//     }
//
//     printf("%d %d %d\n", nb, nt, nl);
// }


// main()
// {
//     int c, nl;
//
//     nl = 0;
//     while ( (c = getchar()) != EOF )
//         if (c == '\n')
//             ++nl;
//
//     printf("%d\n", nl);
// }

// main()
// {
//     double nc;
//
//     for (nc = 0; getchar() != EOF; ++nc)
//         ;
//
//     printf("%.0f\n", nc);
// }


// main()
// {
//     long nc;
//
//     nc = 0;
//     while (getchar() != EOF)
//         ++nc;
//
//     printf("%ld\n", nc);
// }



// 1-7
// main()
// {
//     printf("%d\n", EOF);
// }



// 1-6
// main()
// {
//     int c = getchar() != EOF;
//     printf("%d\n", c);
// }


// main()
// {
//     int c;
//
//     while ( (c = getchar()) != EOF ) 
//         putchar(c);
// }

// main()
// {
//     int c;
//
//     c = getchar();
//     while (c != EOF) {
//         putchar(c);
//         c = getchar();
//     }
// }