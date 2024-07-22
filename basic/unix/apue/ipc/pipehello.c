#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define  MAXLINE 4096 
#define DEF_PAGER    "/bin/more"   

int main(int argc, char *argv[])
{
    int n;
    int fd[2];
    pid_t pid;
    char  *pager, *argv0;
    char  line[MAXLINE];
    FILE  *fp;

    if (argc != 2) {
        printf("usage: %s <pathname>\n", argv[0]);
        exit(0);
    }

    if ( (fp = fopen(argv[1], "r")) == NULL ) {
        printf("fopen(%s) error.\n", argv[1]);
        exit(1);
    }

    if (pipe(fd) < 0) {
        printf("pipe error.\n");
        exit(1);
    }

    if ( (pid = fork()) < 0 ) {
        printf("fork error.\n");
        exit(1);
    } else if (pid > 0) {
        close(fd[0]);

        while (fgets(line, MAXLINE, fp) != NULL) {
            n = strlen(line);
            if (write(fd[1], line, n) != n) {
                printf("write error.\n");
                exit(1);
            }
        }

        if (ferror(fp)) {
            printf("fgets error.\n");
            exit(1);
        }

        close(fd[1]);

        if (waitpid(pid, NULL, 0) < 0) {
            printf("waitpid error.\n");
            exit(1);
        }
    } else {
        close(fd[1]);

        if (fd[0] != STDIN_FILENO) {
            if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO) {
                printf("dup2 error.\n");
                exit(1);
            }

            close(fd[0]);
        }

        if ( (pager = getenv("PAGER")) == NULL )
            pager = DEF_PAGER;

        if ( (argv0 = strrchr(pager, '/')) != NULL )
            argv0++;
        else
            argv0 = pager;

        if (execl(pager, argv0, (char *)0) < 0) {
            printf("execl error.\n");
            exit(1);
        }
    }

    exit(0);
}


















// #define  MAXLINE 4096  

// int main(void)
// {
//     int n;
//     int fd[2];
//     pid_t pid;
//     char line[MAXLINE];

//     if (pipe(fd) < 0) {
//         printf("pipe error\n");
//         exit(1);
//     }

//     if ( (pid = fork()) < 0) {
//         printf("fork error\n");
//         exit(1);
//     } else if (pid > 0) {
//         close(fd[0]);
//         write(fd[1], "hello world\n", 12);
//     } else {
//         close(fd[1]);
//         n = read(fd[0], line, MAXLINE);
//         write(STDOUT_FILENO, line, n);
//     }

//     exit(0);
// }