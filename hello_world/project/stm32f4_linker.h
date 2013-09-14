/*==================================================================================================

	stm32f4_linker.h
	
	This file contains linker definitions which may be used along the application code, such as
	binary section addresses.

 ===================================================================================================

	Author: Henrique Persico Rossi
	e-mail: henriqueprossi@gmail.com

 =================================================================================================*/

#ifndef _STM32F4_LINKER_H_
#define _STM32F4_LINKER_H_

/*==================================================================================================
  INCLUDE FILES
==================================================================================================*/


/*==================================================================================================
  GLOBAL DEFINITIONS
==================================================================================================*/


/*==================================================================================================
  GLOBAL TYPEDEFS
==================================================================================================*/


/*==================================================================================================
  GLOBAL VARIABLES
==================================================================================================*/

extern unsigned long _etext;
extern unsigned long _sidata;		/* start address for the initialization values
                                   of the .data section. defined in linker script */
extern unsigned long _sdata;		/* start address for the .data section. defined
                                   in linker script */
extern unsigned long _edata;		/* end address for the .data section. defined in
                                   linker script */

extern unsigned long _sbss;			/* start address for the .bss section. defined
                                   in linker script */
extern unsigned long _ebss;			/* end address for the .bss section. defined in
                                   linker script */

extern unsigned long _estack;		/* init value for the stack pointer. defined in linker script */

/*==================================================================================================
  GLOBAL FUNCTIONS
==================================================================================================*/

#endif /* _STM32F4_LINKER_H_ */

