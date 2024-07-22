#include "../../common/wrap_sys_type.h"
#include "../../common/wrap_sys_iocall.h"
#include "../../common/wrap_sys_ipc.h"
#include "../../common/err_func.h"


int main(int argc, char **argv)
{
    int32_t c, oflag, msqid;

    oflag = FILE_MODE | IPC_CREAT;
    while ( (c = Getopt(argc, argv, "e")) != -1 ) {
        switch (c) {
            case 'e':
                oflag |= IPC_EXCL;
                break;
        }
    }
    if (optind != argc - 1)
        err_quit("usage: msgcreate [ -e ] <pathname>");

    msqid = Msgget(Ftok(argv[optind], 0), oflag);
    exit(0);
}