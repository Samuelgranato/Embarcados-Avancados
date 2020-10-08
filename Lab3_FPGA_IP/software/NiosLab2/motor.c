/*
 * motor.c
 *
 *  Created on: Sep 30, 2020
 *      Author: labarqcomp
 */

#include "motor.h"
#include "system.h"

// LED Peripheral
#define REG_DATA_OFFSET 1
#define REG_DATA_MOTOR_OFFSET 0
#define REG_DATA_MASK_MOTOR_ENABLE 1 << 0
#define REG_DATA_MASK_MOTOR_DIR 1 << 1
#define REG_DATA_MASK_MOTOR_QUARTER 1 << 2
#define REG_DATA_MASK_MOTOR_VEL 3 << 3



// Para rubrica C
int motor_init(unsigned int *p_motor){
	// Inicializa o periferico

	*(p_motor+REG_DATA_MOTOR_OFFSET) = REG_DATA_MASK_MOTOR_ENABLE;

	return 0;
}
int motor_halt(unsigned int *p_motor){
	// Desativa o periferico

	*(p_motor+REG_DATA_MOTOR_OFFSET) &= ~(REG_DATA_MASK_MOTOR_ENABLE);

	return 0;
}
int motor_en(unsigned int *p_motor){
	// girar uma volta completa

	*(p_motor+REG_DATA_MOTOR_OFFSET) |= REG_DATA_MASK_MOTOR_QUARTER;
	usleep(500000);
	*(p_motor+REG_DATA_MOTOR_OFFSET) &= ~(REG_DATA_MASK_MOTOR_QUARTER);


	return 0;
}

// Para rubrica B/A
int motor_dir(unsigned int *p_motor, int is_clockwise){
	// configura direcao

	*(p_motor+REG_DATA_MOTOR_OFFSET) &= ~(REG_DATA_MASK_MOTOR_DIR);
	usleep(50000);
	*(p_motor+REG_DATA_MOTOR_OFFSET) |= REG_DATA_MASK_MOTOR_DIR;

	return 0;
}
int motor_vel(unsigned int *p_motor, int vel){
	// configura velocidade

	*(p_motor+REG_DATA_MOTOR_OFFSET) &= ~(REG_DATA_MASK_MOTOR_VEL);
	usleep(50000);
	*(p_motor+REG_DATA_MOTOR_OFFSET) |= (vel << 3);

	return 0;
}

