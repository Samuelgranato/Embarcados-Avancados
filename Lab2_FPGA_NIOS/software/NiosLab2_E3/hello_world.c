#include <stdio.h>
#include "system.h"
#include <alt_types.h>
#include <io.h> /* Leiutura e escrita no Avalon */

//#define SIM

// LED Peripheral
#define REG_DATA_OFFSET 1

int main(void){
  unsigned int led = 0;
  unsigned int *p_led = (unsigned int *) PERIPHERAL_LED_OK_0_BASE;

#ifndef SIM
  printf("Embarcados++ \n");
#endif

  while(1){
      if (led < 4){
          *(p_led+REG_DATA_OFFSET) = (0x1 << led++);
#ifndef SIM
          usleep(500000); // remover durante a simula
#endif
      }
      else{
          led = 0;
      }
  };

  return 0;
}
