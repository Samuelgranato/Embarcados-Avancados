/*
 * motor.h
 *
 *  Created on: Sep 30, 2020
 *      Author: labarqcomp
 */

#ifndef MOTOR_H_
#define MOTOR_H_

// Para rubrica C
int motor_init(unsigned int *p_motor);        // Inicializa o periferico
int motor_halt(unsigned int *p_motor);        // Desativa o periferico
int motor_en(unsigned int *p_motor);  		// girar uma volta completa

// Para rubrica B/A
int motor_dir(unsigned int *p_motor, int is_clockwise);      // configura direcao
int motor_vel(unsigned int *p_motor, int vel);    // condigura velocidade



#endif /* MOTOR_H_ */
