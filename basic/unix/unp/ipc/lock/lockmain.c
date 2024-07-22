#include "../../common/err_func.h"
#include "../../common/wrap_sys_iocall.h"
#include "mylock.h"

#define SEQFILE "seqno"

int main(int argc, char **argv)
{
    int32_t fd;
    long i, seqno;
    pid_t pid;
    int32_t n;
    int8_t line[MAXLINE + 1];

    pid = getpid();
    fd = Open(SEQFILE, O_RDWR, FILE_MODE);

    for (i = 0; i < 20; i++) {
        my_lock(fd);

        lseek(fd, 0L, SEEK_SET);
        n = Read(fd, line, MAXLINE);
        line[n] = '\0';

        n = sscanf(line, "%ld\n", &seqno);
        printf("%s: pid = %ld, seq# = %ld\n", argv[0], (long)pid, seqno);

        seqno++;

        snprintf(line, sizeof(line), "%ld\n", seqno);
        lseek(fd, 0L, SEEK_SET);
        Write(fd, line, strlen(line));

        my_unlock(fd);
    }

    exit(0);
}