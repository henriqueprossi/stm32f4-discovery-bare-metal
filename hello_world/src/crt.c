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
  pdwSource	= &_etext;
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

