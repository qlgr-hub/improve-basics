#include "wrap_std_alloc.h"

void *Malloc(uint32_t size)
{
    void *ptr;

	if ( (ptr = malloc(size)) == NULL ) {
#ifdef _UNP_DEMO_
        err_sys("malloc error");
#endif // _UNP_DEMO_
    }
	
	return(ptr);
}

void *Calloc(uint32_t size, uint32_t size_type)
{
    void *ptr;

	if ( (ptr = calloc(size, size_type)) == NULL ) {
#ifdef _UNP_DEMO_
        err_sys("calloc error");
#endif // _UNP_DEMO_
    }
	
	return(ptr);
}