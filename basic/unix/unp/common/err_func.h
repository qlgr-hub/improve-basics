#ifndef _ERR_FUNC_H_
#define _ERR_FUNC_H_

#include "wrap_sys_type.h"

void err_ret(const int8_t *fmt, ...);
void err_sys(const int8_t *fmt, ...);
void err_dump(const int8_t *fmt, ...);
void err_msg(const int8_t *fmt, ...);
void err_quit(const int8_t *fmt, ...);


#endif // !_ERR_FUNC_H_