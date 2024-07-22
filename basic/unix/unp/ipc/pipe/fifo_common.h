#ifndef _FIFO_COMMON_H_
#define _FIFO_COMMON_H_

#include "../../common/wrap_sys_type.h"

#define FIFO1  "/tmp/fifo.1"
#define FIFO2  "/tmp/fifo.2"

#define SERV_FIFO "/tmp/fifo.serv"


#define MAXMESGDATA (PIPE_BUF - 2 * sizeof(long))
#define MESGHDRSIZE (sizeof(struct mymesg) - MAXMESGDATA)

struct mymesg {
    long   mesg_len;
    long   mesg_type;
    int8_t mesg_data[MAXMESGDATA];
};

int32_t Mesg_send(int32_t fd, struct mymesg *mptr);
int32_t Mesg_recv(int32_t fd, struct mymesg *mptr);

#endif /* !_FIFO_COMMON_H_ */
