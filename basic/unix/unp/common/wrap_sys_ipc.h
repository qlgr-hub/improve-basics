#ifndef _WRAP_SYS_IPC_H_
#define _WRAP_SYS_IPC_H_

#include "wrap_sys_type.h"

key_t Ftok(const int8_t *pathname, int32_t id);

int32_t Pipe(int32_t fd[2]);

FILE   *Popen(const int8_t *command, const int8_t *type);
int32_t Pclose(FILE *stream);

mqd_t   Mq_open(const int8_t *name, int32_t oflag, ...);
int32_t Mq_close(mqd_t mqdes);
int32_t Mq_unlink(const int8_t *name);
int32_t Mq_getattr(mqd_t mqdes, struct mq_attr *attr);
int32_t Mq_setattr(mqd_t mqdes, const struct mq_attr *attr, struct mq_attr *oattr);
int32_t Mq_send(mqd_t mqdes, const int8_t *ptr, uint32_t len, uint32_t prio);
int32_t Mq_receive(mqd_t mqdes, int8_t *ptr, uint32_t len, uint32_t *priop);
int32_t Mq_notify(mqd_t mqdes, const struct sigevent *notification);

int32_t Msgget(key_t key, int32_t oflag);
int32_t Msgsnd(int32_t msqid, const void *ptr, uint32_t length, int32_t flag);
int32_t Msgrcv(int32_t msqid, void *ptr, uint32_t length, long type, int32_t flag);
int32_t Msgctl(int32_t msqid, int32_t cmd, struct msqid_ds *buff);

#endif /* !_WRAP_SYS_IPC_H_ */
