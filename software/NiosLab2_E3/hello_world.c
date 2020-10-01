#include <stdio.h>
#include "system.h"
#include <alt_types.h>
#include <io.h> /* Leiutura e escrita no Avalon */

//#define SIM

// LED Peripheral
#define REG_DATA_OFFSET 1
#define REG_DATA_MOTOR_OFFSET 0
#define REG_DATA_MASK_MOTOR_ENABLE 1 << 0
#define REG_DATA_MASK_MOTOR_DIR 1 << 1
#define REG_DATA_MASK_MOTOR_QUARTER 1 << 2
#define REG_DATA_MASK_MOTOR_VEL 1 << 3

unsigned int *p_led = (unsigned int *) PERIPHERAL_LED_OK_0_BASE;
unsigned int *p_motor = (unsigned int *) PERIPHERAL_MOTOR_0_BASE;


void set_speed(int vel){
	*(p_motor+REG_DATA_MOTOR_OFFSET) = REG_DATA_MASK_MOTOR_ENABLE | REG_DATA_MASK_MOTOR_DIR | (REG_DATA_MASK_MOTOR_VEL & vel << 3);
}

void set_dir(int is_clockwise){
	*(p_motor+REG_DATA_MOTOR_OFFSET) = REG_DATA_MASK_MOTOR_ENABLE | ( REG_DATA_MASK_MOTOR_DIR & is_clockwise << 1);
}

void set_enable(int enable){
	*(p_motor+REG_DATA_MOTOR_OFFSET) = REG_DATA_MASK_MOTOR_ENABLE && enable;
}

void set_quarter(){
	*(p_motor+REG_DATA_MOTOR_OFFSET) = REG_DATA_MASK_MOTOR_ENABLE | REG_DATA_MASK_MOTOR_QUARTER;

}

int main(void){
  printf("Embarcadios++ \n");

  while(1){
	  printf("Setando para parar \n");
	  set_enable(0);
	  printf("%04x \n",*(p_motor+REG_DATA_MOTOR_OFFSET));
	  usleep(5000000);

	  printf("Setando para rodar \n");
	  set_enable(1);
	  printf("%04x \n",*(p_motor+REG_DATA_MOTOR_OFFSET));
	  usleep(5000000);

	  printf("Setando para mudar direcao \n");
	  set_dir(1);
	  printf("%04x \n",*(p_motor+REG_DATA_MOTOR_OFFSET));
	  usleep(5000000);

	  printf("Setando para aumentar a velocidade \n");
	  set_speed(3);
	  printf("%04x \n",*(p_motor+REG_DATA_MOTOR_OFFSET));
	  usleep(10000000);

	  printf("Setando para diminuir velocidade e depois dar um 360 \n");
	  set_speed(0);
	  usleep(300000);
	  set_quarter(1);
	  printf("%04x \n",*(p_motor+REG_DATA_MOTOR_OFFSET));
	  usleep(10000000);

  }

  return 0;
}
