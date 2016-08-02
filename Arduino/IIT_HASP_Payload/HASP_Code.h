#ifndef HASP_CODE_H
#define HASP_CODE_H

/*********************************/
/************ INCLUDES ***********/
/*********************************/

#include "Arduino.h"


/**********************************************/
/***************** DEFINES ********************/
/**********************************************/

#define NUMBER_OF_SENSORS     5

#define SENSARRAY_PRESSURE    0
#define SENSARRAY_ALTITUDE    1
#define SENSARRAY_TEMP        2
#define SENSARRAY_GEIGER      3
#define SENSARRAY_CURRENT     4


#define CURRENTSENSOR_PIN     0  // analog
#define CAMERA_PIN           35
#define GYRO_PIN             30
#define GEIGER_PIN           40

/**
 * GPS Enable - D1 (unused)
 * Card Reader Tx1 - D18
 * Card Reader Rx1 - D19
 * SDN - A6
 * NIRQ - A5
 * Card Select 4 - A4
 * Card Select 3 - A3
 * CS2 (tranceiver) - A2 (would need to solder CLK, uses SPI)
 * CS1 - A1
 * Current Sensor - A0
 * MPU6050 - SCL1, SDA1
 * Geiger - A1 (soldered to D30)
 * MS58603 - SDA1, SCL1
 * Copernicus - Tx1 (D18), Rx1(D19)
 * HackHD - solder pin D35
 */

#endif
