/*==================================================================================================

  hello_world.c

  Used hardware: STM32F4 - Discovery evaluation board

  ==================================================================================================

  Author: Henrique Persico Rossi
  e-mail: henriqueprossi@gmail.com

  ================================================================================================*/

/*==================================================================================================
  INCLUDE FILES
==================================================================================================*/

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "project.h"
#include <stdint.h>
#include <stdlib.h>

/*=================================================================================================
  LOCAL DEFINITIONS
=================================================================================================*/

#define DELAY_1000_MS   1000u

/*==================================================================================================
  LOCAL FUNCTIONS
==================================================================================================*/

static void busy_wait(const uint32_t ticks_to_wait);

/*==================================================================================================
  LOCAL VARIABLES
==================================================================================================*/

static GPIO_InitTypeDef   GPIO_InitStructure;
static volatile uint32_t  ticks;

/*==================================================================================================
  Function    : busy_wait

  Description : It forces a busy wait of the number of ticks specified by the argument which is
                passed in the function.

  Parameters  : ticks_to_wait [IN] Number of ticks to be busy-waited

  Returns     : None
==================================================================================================*/

static void busy_wait(const uint32_t ticks_to_wait)
{
  const uint32_t initial_ticks = ticks;

  while ((ticks - initial_ticks) < ticks_to_wait) ;
}

/*==================================================================================================
  Function    : SysTick_Handler

  Description : Callback function which is called upon SysTick timer interrupt, which takes place
                every 1 ms.

  Parameters  : None

  Returns     : None
==================================================================================================*/

void SysTick_Handler(void)
{
  /* Increment the counter which is necessary for busy-wating. */
  ticks++;
}

/*==================================================================================================
  Function    : main


  Description : Entry point of the user application. It only set/clear the LD3, LD4, LD5 and LD6 leds
                on the board.

  Parameters  : None

  Returns     : EXIT_SUCCESS  Successfull termination

                Otherwise     Error
==================================================================================================*/

int main(void)
{
#ifdef PROJ_TEST_DINAMIC_MEM
  char * pmem;
#endif
#ifdef PROJ_TEST_FLOAT_OPERATION
  float	myfloat1 = 1.25;
  float	myfloat2 = 3.89;
  float	myfloat3;
#endif

  /* At this point the microcontroller clock is already set, which is done through SystemInit()
   * function. This is done by means of the C runtime initialization (crt.c), which, afterwards,
   * call the main application.
   */

   /* Set system tick for 1ms interrupt. */
  SystemCoreClockUpdate();

  if (SysTick_Config(SystemCoreClock / 1000)) {
    for (;;) ;
  }

  /* GPIOD Peripheral clock enable. */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
   
  /* LED's configuration:
   * LD3: GPIO PD13 (0: OFF, 1: ON)
   * LD4: GPIO PD12 (0: OFF, 1: ON)
   * LD5: GPIO PD14 (0: OFF, 1: ON)
   * LD6: GPIO PD15 (0: OFF, 1: ON)
   */

  /* Configure PD12, PD13, PD14 and PD15 in output pushpull mode. */
  GPIO_InitStructure.GPIO_Pin   = LED4_PIN | LED3_PIN | LED5_PIN | LED6_PIN;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  
  GPIO_Init(GPIOD, &GPIO_InitStructure);

#ifdef PROJ_TEST_DINAMIC_MEM
  pmem = (char *) malloc(1024);
  if (!pmem) {
    return 1;
  }
#endif

#ifdef PROJ_TEST_FLOAT_OPERATION
  myfloat3 = myfloat1 * myfloat2;
  if (myfloat3 < 1.00) {
	  return 2;
  }
#endif

  while (1) {
    GPIO_SetBits(GPIOD, LED4_PIN); /* LED4 ON */
    busy_wait(DELAY_1000_MS); /* Keep the LED on for 1 second */
    GPIO_SetBits(GPIOD, LED3_PIN); /* LED3 ON */
    busy_wait(DELAY_1000_MS); /* Keep the LED on for 1 second */
    GPIO_SetBits(GPIOD, LED5_PIN); /* LED5 ON */
    busy_wait(DELAY_1000_MS); /* Keep the LED on for 1 second */
    GPIO_SetBits(GPIOD, LED6_PIN); /* LED6 ON */
    busy_wait(DELAY_1000_MS); /* Keep the LED on for 1 second */
    GPIO_ResetBits(GPIOD, LED4_PIN | LED3_PIN | LED5_PIN | LED6_PIN);  /* All LEDs are OFF. */
    busy_wait(DELAY_1000_MS); /* Keep all LEDs off for 1 second */
  }
  
  return 0;
}

