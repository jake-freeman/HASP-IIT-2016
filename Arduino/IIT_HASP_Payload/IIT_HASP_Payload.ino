#include <Wire.h>
//#include <SoftwareSerial.h>
#include "HASP_Code.h"
#include "HackHD.h"
#include "Tasks.h"
// #include "VCO.h"
// #include <I2C_16.h>
// #include <TMP006.h>
// #include <Adafruit_BMP085.h>
// #include <HUMIDITY_HIH6130.h>
// #include "Comm.h"
// #include <Adafruit_INA219.h>
#include <Wire.h>
#include <MS5803_I2C.h>


/***************************************************/
/*************** TMP006 (Temperature) **************/
/***************************************************/

/* Temperature sensor I2C address */
//uint8_t temp_I2CAddress = 0x40;

/* Number of samples per reading from temperature sensor */
//uint16_t temp_samples = TMP006_CFG_8SAMPLE;



/*************************************************/
/*************** BMP085 (Pressure) ***************/
/*************************************************/

/* Pressure sensor */
//Adafruit_BMP085 bmp;
MS5803 pressure_sensor(ADDRESS_HIGH);



/*************************************************/
/*************** INA219 (Current) ****************/
/*************************************************/

/* Current sensor */
//Adafruit_INA219 ina219;




/*****************************************/
/************** Light sensor *************/
/*****************************************/
/**                                     **/
/**            PhotoR     10K           **/
/**  +5    o---/\/\/--.--/\/\/---o GND  **/
/**                   |                 **/
/**  Pin 0 o-----------                 **/
/**                                     **/
/*****************************************/




/**
 *  Setup.
 *    - BMP085 (Pressure)
 *    - HackHD (Camera)
 *    - HIH6130 (Humidity)
 *    - NASA Serial port
 *    - Communication Serial port
 */
void setup() {

    /* Start serial communication */
    Serial.begin(SERIAL_BAUDRATE);

    /* Trace */
    Serial.println("Start Hasp Program!");
    Serial.flush();

    /* Setup temperature sensor */
    //config_TMP006(temp_I2CAddress, temp_samples);

    /*Setup pressure sensor */
    // if (!bmp.begin()) {
    //     /* If code reaches here, means that the pressure sensor could not be initialized */
    // }
    Wire.begin();
    Serial.println("Wire!");
    Serial.flush();
    pressure_sensor.reset();
    pressure_sensor.begin();

    /* Setup humidity sensor */
    // Wire.begin();

    /* Setup current sensors */
    // ina219.begin();
    // pinMode(CURRENTSENSOR2_PIN, OUTPUT);

    /* Setup HackHD camera */
    //HackHD_setup();

    /* Setup VCO */
    //VCO_setup();

    /* Setup COMMs */
    COMM_setup();
    Serial.println("Com!");
    Serial.flush();
}



/**
 * Loop. Read sensors, read commands and send info.
 */
void loop() {
    //Serial.println("Loop!");
    //Serial.flush();
    /* Run tasks */
    checkTasks();

    /* Read commands from NASA serial port */
    COMM_readSerial();
}
