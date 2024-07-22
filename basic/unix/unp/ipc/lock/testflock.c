#include "../../common/err_func.h"
#include "../../common/wrap_sys_iocall.h"
#include "../../common/wrap_sys_proccall.h"
#include "mylock.h"

int main(int argc, char **argv)
{
    int32_t fd;

    fd = Open("test1.data", O_RDWR | O_CREAT, FILE_MODE);

    Read_lock(fd, 0, SEEK_SET, 0);
    printf("%s: parent has read lock\n", Gf_time());

    if (Fork() == 0) {
        sleep(1);
        printf("%s: first child tries to obtain write lock\n", Gf_time());
        Writew_lock(fd, 0, SEEK_SET, 0);
        printf("%s: first child obtains write lock\n", Gf_time());
        sleep(2);
        Un_lock(fd, 0, SEEK_SET, 0);
        printf("%s: first child releases write lock\n", Gf_time());
        exit(0);
    }

    if (Fork() == 0) {
        sleep(3);
        printf("%s: second child tries to obtain read lock\n", Gf_time());
        Readw_lock(fd, 0, SEEK_SET, 0);
        printf("%s: second child obtains read lock\n", Gf_time());
        sleep(4);
        Un_lock(fd, 0, SEEK_SET, 0);
        printf("%s: second child releases read lock\n", Gf_time());
        exit(0);
    }

    sleep(5);
    Un_lock(fd, 0, SEEK_SET, 0);
    printf("%s: parent releases read lock\n", Gf_time());
    exit(0);
}