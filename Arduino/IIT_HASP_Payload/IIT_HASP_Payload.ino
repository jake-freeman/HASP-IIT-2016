#include "HASP_Code.h"
#include "Tasks.h"

#include <Wire.h>

#include "HackHD.h"
#include <MS5803_I2C.h>


/* Pressure / Temp / Altitude sensor */
MS5803 pressure_sensor(ADDRESS_HIGH);
double BASE_ALTITUDE     = 146.91,  // meters (Palestine, TX)
       pressure_baseline = 0.0;     // set in setup()

/* Geiger Counter (SEN-11345) */
volatile int state = LOW; //volatile because passing data from interrupt to main program


/**
 *  Setup
 *    - MS5803 (Pressure)
 *    - HackHD (Camera)
 *    - NASA Serial port
 *    - SEN-11345 (Geiger)
 */
void setup() {

    /* Start serial communication */
    Serial.begin(SERIAL_BAUDRATE);

    /* Trace */
    Serial.println("Start Hasp Program!");
    Serial.flush();

    /* Setup pressure / temp / altitude sensor */
    Wire.begin();
    pressure_sensor.reset();
    pressure_sensor.begin();
    pressure_baseline = pressure_sensor.getPressure(ADC_4096);

    /* Setup Geiger counter */
    attachInterrupt(digitalPinToInterrupt(GEIGER_PIN), geiger, RISING);

    /* Setup HackHD camera */
    //HackHD_setup();

    /* Setup COMMs */
    COMM_setup();
    Serial.println("Com!");
    Serial.flush();
}



/**
 * Loop. Read sensors, read commands and send info.
 */
void loop() {
    /* Run tasks */
    checkTasks();

    /* Read commands from NASA serial port */
    COMM_readSerial();
}

extern int geiger_count;
void geiger(){
  /**
   * this function is called whenever a geiger event occurs. millis()
   * will be INcorrect after many calls to geiger(). delay will not
   * work inside interrupt.
   */
  geiger_count++; //adds one to count when gieger event occurs
}
