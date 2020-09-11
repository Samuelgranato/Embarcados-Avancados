#include <stdio.h>
#include "system.h"
#include <alt_types.h>
#include <io.h> /* Leiutura e escrita no Avalon */

int delay(int n){
      unsigned int delay = 0 ;
      while(delay < n){
          delay++;
      }
}

int main(void){
  unsigned int led = 0;

  printf("Embarcados++ \n");

  //PIO_0 -> LEDS		0..5
  //PIO_1 -> SWITCHES 	0..3
  //PIO_2 -> BUTTON
  //PIO_3 -> MOTOR 		0..3

  int sw;
  int enable;
  int dir;
  int vel_1;
  int vel_2;

  int phase = 0;
  int sleep = 100000;
  while(1){
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
		  sleep = 2000;
	  }else{
		  if(vel_2){
			  sleep = 10000;
		  }else{
			  if(vel_1){
				  sleep = 20000;
			  }else{
				  sleep = 50000;
			  }
		  }
	  }



	  usleep(sleep);
  };

  return 0;
}
