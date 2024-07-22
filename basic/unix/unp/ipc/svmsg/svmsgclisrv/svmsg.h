#ifndef _SV_MSG_H_
#define _SV_MSG_H_

#include "../../../common/wrap_sys_type.h"

#define MQ_KEY1 1234L
#define MQ_KEY2 1235L

#define MAXMESGDATA (PIPE_BUF - 2 * sizeof(long))
#define MESGHDRSIZE (sizeof(struct mymesg) - MAXMESGDATA)

struct mymesg {
    long   mesg_len;
    long   mesg_type;
    int8_t mesg_data[MAXMESGDATA];
};

int32_t Mesg_send(int32_t id, struct mymesg *mptr);
int32_t Mesg_recv(int32_t id, struct mymesg *mptr);

#endif /* !_SV_MSG_H_ */
