#include <stdio.h>
#include "system.h"
#include <alt_types.h>
#include "motor.h"
#include <io.h> /* Leiutura e escrita no Avalon */

#define REG_DATA_MOTOR_OFFSET 1
unsigned int *p_motor = (unsigned int *) PERIPHERAL_MOTOR_0_BASE;

int main(void){
  printf("Embarcadios++ \n");

  while(1){
	  printf("Inicializando motor \n");
	  motor_init(p_motor);
	  usleep(100000);
	  printf("%04x \n",*(p_motor + REG_DATA_MOTOR_OFFSET));
	  usleep(5000000);

	  printf("Girando uma volta completa \n");
	  motor_en(p_motor);
	  usleep(100000);
	  printf("%04x \n",*(p_motor + REG_DATA_MOTOR_OFFSET));
	  usleep(5000000);

	  printf("Esperando um desacelerar... \n");
	  usleep(100000);
	  printf("%04x \n",*(p_motor + REG_DATA_MOTOR_OFFSET));
	  usleep(12000000);

	  printf("Aumentando a velocidade \n");
	  motor_vel(p_motor,2);
	  usleep(100000);
	  printf("%04x \n",*(p_motor + REG_DATA_MOTOR_OFFSET));
	  usleep(10000000);

	  printf("Diminuindo a velocidade \n");
	  motor_vel(p_motor, 0);
	  usleep(100000);
	  printf("%04x \n",*(p_motor + REG_DATA_MOTOR_OFFSET));
	  usleep(10000000);

	  printf("Mudando a direcao\n");
	  motor_dir(p_motor,1);
	  usleep(100000);
	  printf("%04x \n",*(p_motor + REG_DATA_MOTOR_OFFSET));
	  usleep(10000000);

	  printf("Desativando o motor \n");
	  motor_halt(p_motor);
	  usleep(100000);
	  printf("%04x \n",*(p_motor + REG_DATA_MOTOR_OFFSET));
	  usleep(10000000);



  }

  return 0;
}
