#include "err_func.h"
#include "wrap_sys_ipc.h"

key_t Ftok(const int8_t *pathname, int32_t id)
{
    key_t ret;

	if ( (ret = ftok(pathname, id)) == -1 )
    {
#ifdef _UNP_DEMO_
        err_sys("ftok error");
#endif // _UNP_DEMO_
    }
	
    return (ret);
}

int32_t Pipe(int32_t fd[2])
{
    int32_t	ret;

	if ( (ret = pipe(fd)) < 0 )
    {
#ifdef _UNP_DEMO_
        err_sys("pipe error");
#endif // _UNP_DEMO_
    }
	
    return (ret);
}

FILE *Popen(const int8_t *command, const int8_t *type)
{
    FILE *fp;

	if ( (fp = popen(command, type)) == NULL )
    {
#ifdef _UNP_DEMO_
        err_sys("popen error");
#endif // _UNP_DEMO_
    }
	
    return (fp);
}

int32_t Pclose(FILE *stream)
{
    int32_t	ret;

	if ( (ret = pclose(stream)) < 0 )
    {
#ifdef _UNP_DEMO_
        err_sys("pipe error");
#endif // _UNP_DEMO_
    }
	
    return (ret);
}

mqd_t Mq_open(const int8_t *name, int32_t oflag, ...)
{
    mqd_t	mqd;
	va_list	ap;
	mode_t	mode;
	struct mq_attr	*attr;

	if (oflag & O_CREAT) {
		va_start(ap, oflag);		/* init ap to final named argument */
		mode = va_arg(ap, mode_t);
		attr = va_arg(ap, struct mq_attr *);
		if ( (mqd = mq_open(name, oflag, mode, attr)) == (mqd_t) -1)
		{
#ifdef _UNP_DEMO_
			err_sys("mq_open error for %s", name);
#endif // _UNP_DEMO_
		}
		va_end(ap);
	} else {
		if ( (mqd = mq_open(name, oflag)) == (mqd_t) -1)
		{
#ifdef _UNP_DEMO_
			err_sys("mq_open error for %s", name);
#endif // _UNP_DEMO_
		}
	}
	return(mqd);
}

int32_t Mq_close(mqd_t mqdes)
{
	int32_t ret;
	if ( (ret = mq_close(mqdes)) == -1 ) 
	{
#ifdef _UNP_DEMO_
		err_sys("mq_close error");
#endif // _UNP_DEMO_
	}

	return ret;
}

int32_t Mq_unlink(const int8_t *name)
{
	int32_t ret;
	if ( (ret = mq_unlink(name)) == -1 ) 
	{
#ifdef _UNP_DEMO_
		err_sys("mq_unlink error");
#endif // _UNP_DEMO_
	}

	return ret;
}

int32_t Mq_getattr(mqd_t mqdes, struct mq_attr *attr)
{
	int32_t ret;
	if ( (ret = mq_getattr(mqdes, attr)) == -1 ) 
	{
#ifdef _UNP_DEMO_
		err_sys("mq_getattr error");
#endif // _UNP_DEMO_
	}

	return ret;
}

int32_t Mq_setattr(mqd_t mqdes, const struct mq_attr *attr, struct mq_attr *oattr)
{
	int32_t ret;
	if ( (ret = mq_setattr(mqdes, attr, oattr)) == -1 ) 
	{
#ifdef _UNP_DEMO_
		err_sys("mq_setattr error");
#endif // _UNP_DEMO_
	}

	return ret;
}

int32_t Mq_send(mqd_t mqdes, const int8_t *ptr, uint32_t len, uint32_t prio)
{
	int32_t ret;
	if ( (ret = mq_send(mqdes, ptr, len, prio)) == -1 ) 
	{
#ifdef _UNP_DEMO_
		err_sys("mq_send error");
#endif // _UNP_DEMO_
	}

	return ret;
}

int32_t Mq_receive(mqd_t mqdes, int8_t *ptr, uint32_t len, uint32_t *priop)
{
	int32_t ret;
	if ( (ret = mq_receive(mqdes, ptr, len, priop)) == -1 ) 
	{
#ifdef _UNP_DEMO_
		err_sys("mq_receive error");
#endif // _UNP_DEMO_
	}

	return ret;
}

int32_t Mq_notify(mqd_t mqdes, const struct sigevent *notification)
{
	int32_t ret;
	if ( (ret = mq_notify(mqdes, notification)) == -1 ) 
	{
#ifdef _UNP_DEMO_
		err_sys("mq_notify error");
#endif // _UNP_DEMO_
	}

	return ret;
}

int32_t Msgget(key_t key, int32_t oflag)
{
	int32_t ret;
	if ( (ret = msgget(key, oflag)) == -1 ) 
	{
#ifdef _UNP_DEMO_
		err_sys("msgget error");
#endif // _UNP_DEMO_
	}

	return ret;
}

int32_t Msgsnd(int32_t msqid, const void *ptr, uint32_t length, int32_t flag)
{
	int32_t ret;
	if ( (ret = msgsnd(msqid, ptr, length, flag)) == -1 ) 
	{
#ifdef _UNP_DEMO_
		err_sys("msgsnd error");
#endif // _UNP_DEMO_
	}

	return ret;
}

int32_t Msgrcv(int32_t msqid, void *ptr, uint32_t length, long type, int32_t flag)
{
	int32_t ret;
	if ( (ret = msgrcv(msqid, ptr, length, type, flag)) == -1 ) 
	{
#ifdef _UNP_DEMO_
		err_sys("msgrcv error");
#endif // _UNP_DEMO_
	}

	return ret;
}

int32_t Msgctl(int32_t msqid, int32_t cmd, struct msqid_ds *buff)
{
	int32_t ret;
	if ( (ret = msgctl(msqid, cmd, buff)) == -1 ) 
	{
#ifdef _UNP_DEMO_
		err_sys("msgctl error");
#endif // _UNP_DEMO_
	}

	return ret;
}
