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


#define CURRENTSENSOR_PIN     2  // analog
#define CAMERA_PIN           51
#define GEIGER_PIN           22

#endif
