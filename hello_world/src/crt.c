/*==================================================================================================

  crt.c

  C Runtime initialization module

  ==================================================================================================

  Author: Henrique Persico Rossi
  e-mail: henriqueprossi@gmail.com

  =================================================================================================*/

/*==================================================================================================
  INCLUDE FILES
==================================================================================================*/

#include <stdint.h>
#include "crt.h"
#include "system_stm32f4xx.h"
#include "stm32f4_linker.h" /* Sections and symbols which are defined by the linker script */
#include "hello_world.h"    /* This is where the main function is declared */
//#include <errno.h>
#include <unistd.h>
#include <malloc.h>

//#undef errno
//extern int errno;

//#define HEAPSIZE    0x400
//#define STACKSIZE   0x400

//unsigned char __attribute__((section(".heap"))) _heap[HEAPSIZE];
//unsigned char __attribute__((section(".stack"))) _stack[STACKSIZE];

/*==================================================================================================
  Function    : Reset_Handler

  Description : This function is used for C runtime initialization, which is the code that gets
                called when the processor first starts execution following a reset event. Only
                the absolutely necessary set is performed, which includes handling the .data and
                .bss segments, after which the application supplied main() routine is called.

  Parameters  : None

  Returns     : None
==================================================================================================*/

void Reset_Handler(void)
{
  uint32_t	*	pdwSource;
  uint32_t	*	pdwDest;
  int					iRetMain;

  /* Copy the initialized data of the ".data" segment from the FLASH to the area in the RAM. */
  pdwSource	= &_sidata;
  pdwDest		= &_sdata;

  while (pdwDest < &_edata) {
    *pdwDest = *pdwSource;
    pdwDest++;
    pdwSource++;
  }

  /* Clear the ".bss" segment */
  pdwDest = &_sbss;

  while (pdwDest < &_ebss) {
    *pdwDest++ = 0;
  }

  /* Call the SystemInit code from CMSIS interface */
  SystemInit();

  /* The runtime environment is set. So, the main function is called */
  iRetMain = main();
  (void) iRetMain;

  /* If it is necessary handling any error status from main function, it may be done here. */
  for (;;) ;
}

#if 0
int open(const char *name, int flags, int mode)
{
  return -1;
}

int close(int file)
{
  return -1;
}

int read(int file, void *ptr, size_t len)
{
  return 0;
}

int write(int file, const void *ptr, size_t len)
{
  int todo;
  
  for (todo = 0; todo < len; todo++) {
    //writechar(*ptr++);
  }
  
  return len;
}

void * _sbrk(ptrdiff_t incr)
{
//  extern char   end;    /* Defined by the linker */
  static char * heap_end = NULL;
  char        * prev_heap_end;

  if (heap_end == NULL) {
    heap_end = (char *) &end;
  }
  
  prev_heap_end = heap_end;
  
  if ((heap_end + incr) >= (char *) &_stack_end) {
    errno = ENOMEM;
    return NULL;
  }

  heap_end += incr;
  return (void *) prev_heap_end;
}
#endif

caddr_t _sbrk(int incr)
//void * _sbrk(ptrdiff_t incr)
{
  static unsigned char  * heap = NULL;
  unsigned char         * prev_heap_end;

  if (heap == NULL) {
    heap = (unsigned char *) &_heap_start;
  }
  
  prev_heap_end = heap;
  
  if ((heap + incr) > (unsigned char *) &_heap_end) {
    //errno = ENOMEM;
    return NULL;
  }

  heap += incr;
  return (caddr_t) prev_heap_end;
//  return (void *) prev_heap_end;
}
/*
void __malloc_lock(struct _reent *reent)
{

}

void __malloc_unlock(struct _reent *reent)
{

}
*/

