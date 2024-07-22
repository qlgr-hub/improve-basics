#include <stdio.h>


// 1-5
// main()
// {
//     int fahr;
//
//     for (fahr = 300; fahr >= 0; fahr = fahr - 20)
//         printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
// }

#define LOWER 0
#define UPPER 300
#define STEP  20

main()
{
    int fahr;

    for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
        printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
}

// 1-4
// main()
// {
//     float fahr, celsius;
//     float lower, upper, step;
//
//     lower = 0;
//     upper = 300;
//     step = 20;
//
//     printf("Celsius\tFahr\n"); // 1-3
//     celsius = lower;
//     while (celsius <= upper) {
//         fahr = (9.0*celsius) / 5.0 + 32.0;
//         printf("%3.0f\t%6.1f\n", celsius, fahr);
//         celsius = celsius + step;
//     }
// }

// main()
// {
//     float fahr, celsius;
//     float lower, upper, step;
//
//     lower = 0;
//     upper = 300;
//     step = 20;
//
//     printf("Fahr\tCelsius\n"); // 1-3
//     fahr = lower;
//     while (fahr <= upper) {
//         celsius = (5.0/9.0) * (fahr-32.0);
//         printf("%3.0f\t%6.1f\n", fahr, celsius);
//         fahr = fahr + step;
//     }
// }

// main()
// {
//     int fahr, celsius;
//     int lower, upper, step;
//
//     lower = 0;
//     upper = 300;
//     step = 20;
//
//     fahr = lower;
//     while (fahr <= upper) {
//         celsius = 5 * (fahr - 32) / 9;
//         printf("%d\t%d\n", fahr, celsius);
//         fahr = fahr + step;
//     }
// }