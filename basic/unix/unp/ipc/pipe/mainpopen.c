#include "../../common/err_func.h"
#include "../../common/wrap_sys_ipc.h"
#include "../../common/wrap_sys_iocall.h"
#include "../../common/wrap_sys_proccall.h"
#include "../../common/wrap_sys_sockcall.h"

int main(int argc, char *argv[])
{
    uint32_t n;
    int8_t buff[MAXLINE], command[MAXLINE];
    FILE *fp;

    Fgets(buff, MAXLINE, stdin);
    n = strlen(buff);
    if (buff[n - 1] == '\n')
        n--;

    snprintf(command, sizeof(command), "cat %s", buff);
    fp = Popen(command, "r");

    while (Fgets(buff, MAXLINE, fp) != NULL)
        Fputs(buff, stdout);

    Pclose(fp);
    exit(0);
}