/*
 * API_controller_gate.h
 *
 *  Created on: 5 dic. 2021
 *      Author: alex
 */

#ifndef API_INC_API_CONTROLLER_GATE_H_
#define API_INC_API_CONTROLLER_GATE_H_

#include <stdio.h>
#include "API_sensor.h"

/* Definition state motor */
#define MOTOR_DOWN	0
#define MOTOR_UP 	1
#define MOTOR_STOP 	2

/* Typedef -----------------------------------------------------------*/
typedef bool bool_t;

/* Private function prototypes -----------------------------------------------*/
/**
 * @brief Initiliaze the gate state
 * @param sensors Initial sensors values
 * @return 1: Ok, 0: Not Ok
 */
bool_t controllerGateInit(sensor_t * sensors);
/**
 * @brief Gate controller Finite State Machine
 * @param sensors Sensors values
 * @return 0 -> MOTOR_DOWN
 * @return 1 -> MOTOR_UP
 * @return 2 -> MOTOR_STOP
 */
uint8_t controllerGateUpdate(sensor_t * sensors);
/**
 * @brief Get the state of the finite state machine
 * @param state String where it stores the status of the FSM
 * @return None
 */
void controllerGetState(char * state);

#endif /* API_INC_API_CONTROLLER_GATE_H_ */
