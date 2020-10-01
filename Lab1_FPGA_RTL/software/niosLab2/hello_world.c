#include <stdio.h>
#include "system.h"
#include <alt_types.h>
#include <io.h> /* Leiutura e escrita no Avalon */
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"
#include <unistd.h>

int delay(int n){
      unsigned int delay = 0 ;
      while(delay < n){
          delay++;
      }
}

int n = 0;
volatile int edge_capture;
void init_pio();

void handle_button_interrupts(void* context, alt_u32 id)
{
    /* Cast context to edge_capture's type. It is important that this be
     * declared volatile to avoid unwanted compiler optimization.
     */
    volatile int* edge_capture_ptr = (volatile int*) context;
    /* Store the value in the Button's edge capture register in *context. */
    *edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIO_2_BASE);
    n++;
    /* Reset the Button's edge capture register. */
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_2_BASE, 0);


    IOWR_32DIRECT(PIO_0_BASE, 0, 0x01 << 5);


}

/* Initialize the pio. */

void init_pio()
{
    /* Recast the edge_capture pointer to match the alt_irq_register() function
     * prototype. */
    void* edge_capture_ptr = (void*) &edge_capture;
    /* Enable first four interrupts. */
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_2_BASE, 0x1);
    /* Reset the edge capture register. */
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_2_BASE, 0x0);
    /* Register the interrupt handler. */
    alt_irq_register( PIO_2_IRQ, edge_capture_ptr,
                      handle_button_interrupts );
}




int main(void){


  printf("Embarcados++ \n");

  //PIO_0 -> LEDS		0..5
  //PIO_1 -> SWITCHES 	0..3
  //PIO_2 -> BUTTON
  //PIO_3 -> MOTOR 		0..3

  n = 0;
  init_pio();


  int sw;
  int enable;
  int dir;
  int vel_1;
  int vel_2;

  int phase = 0;
  int target_sleep = 100000;

  int sleep = 0;
  while(1){
	  IOWR_ALTERA_AVALON_PIO_DATA(PIO_2_BASE, n);

	  sw 		= IORD_32DIRECT(PIO_1_BASE, 0);
	  enable 	= sw & 0x01;
	  dir 		= sw & 0x02;

	  vel_1 	= sw & 0x04;
	  vel_2		= sw & 0x08;


	  if(dir){
		  phase++;

		  if(phase > 3){
			  phase = 0;
		  }
	  }else{
		  phase--;

		  if(phase < 0){
			  phase = 3;
		  }
	  }




	  if(enable){
		  IOWR_32DIRECT(PIO_0_BASE, 0, 0x01 << phase);
		  IOWR_32DIRECT(PIO_3_BASE, 0, 0x01 << phase);
	  }


	  if(vel_1 && vel_2){
		  target_sleep = 2000;
	  }else{
		  if(vel_2){
			  target_sleep = 7500;
		  }else{
			  if(vel_1){
				  target_sleep = 20000;
			  }else{
				  target_sleep = 40000;
			  }
		  }
	  }

	  if(sleep > target_sleep + 50){
		  sleep = sleep - (sleep - target_sleep)/50;

	  }else{
		  if(sleep < target_sleep - 50){
			  sleep = sleep + (target_sleep - sleep)/250;
		  }
	  }


	  usleep(sleep);
  };

  return 0;
}
