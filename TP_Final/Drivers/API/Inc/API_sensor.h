/*
 * API_sensor.h
 *
 *  Created on: 5 dic. 2021
 *      Author: alex
 */

#ifndef API_INC_API_SENSOR_H_
#define API_INC_API_SENSOR_H_

#include <stdio.h>
#include <stdbool.h>

/* Typedef -----------------------------------------------------------*/
typedef bool bool_t;
typedef enum{notDetect, detect} state_t;
/**
 * @brief Struct of the sensor used
 */
typedef struct{
	state_t readerRFID;
	state_t loopDetector;
	state_t limitSwitchTop;
	state_t	limitSwitchBottom;
} sensor_t;

/* Public function prototypes -----------------------------------------------*/
/**
 * @brief Initiliaze sensor state
 * @param sensorInfo -> Buffer where the initial state of the sensors is stored
 * @return 1: Ok, 0: Not Ok
 */
bool_t sensorInit(sensor_t * sensorInfo);

/**
 * @brief Update the sensors output
 * @param commad -> Input character representing the status of some sensor
 * @param sensorInfo -> Buffer where the state of the sensors is stored
 * @return None
 */
void sensorUpdateState(uint8_t command, sensor_t * sensorInfo);

/**
 * @brief Get the status of the RFID reader
 * @param None
 * @return 1: Detect tag passive, 0: Not detect tag passive
 */
bool_t readerRFID_getState(void);

/**
 * @brief Get the status of the vehicle loop detector
 * @param None
 * @return 1: Detect passing vehicle, 0: Not detect passing vehicle
 */
bool_t loopDetector_getState(void);

/**
 * @brief Get the status limit switch Top
 * @param None
 * @return 1: closed contact, 0: open contact
 */
bool_t  limitSwitchTop_getState(void);

/**
 * @brief Get the status limit switch Bottom
 * @param None
 * @return 1: closed contact, 0: open contact
 */
bool_t limitSwitchBottom_getState(void);

#endif /* API_INC_API_SENSOR_H_ */
