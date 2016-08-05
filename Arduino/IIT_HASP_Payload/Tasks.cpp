#include "Tasks.h"

#include <Wire.h>
#include <MS5803_I2C.h>

/* Serial output for debugging */
#define debug(out) Serial.println(out); Serial.flush();

/* Stores the current time in milliseconds */
unsigned long currentTime;

/* Stores the last moment in which each sensor was sampled */
unsigned long timeTasks[NUMBER_OF_TASKS];

/* Stores the last sampled value of each sensor */
double sensorValues[NUMBER_OF_SENSORS];

/* Pressure sensor */
extern MS5803 pressure_sensor;
extern double base_altitude,
              pressure_baseline;
#define altitude(P, P0) (44330.0 * (1.0 - pow(P / P0, 1.0 / 5.255)));

/* Geiger Counter */
int geiger_count = 0; // to count events from geiger counter


/**
 * Task to read the Pressure sensor
 */
void Task_readPressureAltTempSensor() {
    if (currentTime - timeTasks[TASK_PRESSURE] > TASKPERIOD_PRESSURE) {
        // To measure to higher degrees of precision use the following sensor settings:
        // ADC_256
        // ADC_512
        // ADC_1024
        // ADC_2048
        // ADC_4096

        // Read pressure from the sensor in mbar.
        debug("Read Pressure!");
        double pressure_abs = pressure_sensor.getPressure(ADC_4096);
        sensorValues[SENSARRAY_PRESSURE] = pressure_abs;
        debug(pressure_abs);

        // Read temperature from the sensor in deg C, store in K * 10
        debug("Temperature!");
        double temperature_c = pressure_sensor.getTemperature(CELSIUS, ADC_512);
        sensorValues[SENSARRAY_TEMP] = (double)(temperature_c + 273.00);
        debug(temperature_c);

        // Taking our baseline pressure at the beginning we can find an approximate
        // change in altitude based on the differences in pressure.
        debug("Altitude Delta!")
        double altitude_delta = altitude(pressure_abs , pressure_baseline);
        sensorValues[SENSARRAY_ALTITUDE] = altitude_delta;
        debug(altitude_delta);

        timeTasks[TASK_PRESSURE] = currentTime;
    }
}

/**
 * Task to read the Geiger counter
 */
 void Task_readGeigerCounter() {
    if (currentTime - timeTasks[TASK_GEIGER] > TASKPERIOD_GEIGER) {
        debug("Read Geiger!");
        int current_count = geiger_count;
        geiger_count = 0;
        sensorValues[SENSARRAY_GEIGER] = current_count;
        debug(current_count);

        timeTasks[TASK_GEIGER] = currentTime;
    }
 }

 /**
  * Task to read current sensor
  */
 void Task_readCurrentSensor() {
     if (currentTime - timeTasks[TASK_CURRENT] > TASKPERIOD_CURRENT) {
         debug("Read Current!");
         int current_raw = analogRead(CURRENTSENSOR_PIN);
         double current_volts = (double)(current_raw) * (5.0 / 1024.0),
                current_amps  = (current_volts - 2.5) * 0.185;

         double current = current_amps;
         sensorValues[SENSARRAY_CURRENT] = current;
         debug(current);

         timeTasks[TASK_CURRENT] = currentTime;
     }
 }


/**
 * Task to send the sensors over Serial communication
 */
void Task_sendSensors() {
    if (currentTime - timeTasks[TASK_SENDSENSORS] > TASKPERIOD_SENDSENSORS) {
        debug("Send sensors!");
        COMM_sendSensors(sensorValues, currentTime);
        timeTasks[TASK_SENDSENSORS] = currentTime;
        debug("");
    }
}


/**
 * Task for the HackHD to record 10 minutes. Stops the camera when the 10 minutes have passed.
 */
void Task_record10Minutes() {
    /* If the recording is not active, exit the function */
    if (!HackHD_getHackHDRecordTenMin()) {
        timeTasks[TASK_RECORDTENMIN] = currentTime;
        return;
    }

    if (currentTime - timeTasks[TASK_RECORDTENMIN] > TASKPERIOD_RECORDTENMIN) {
        HackHD_startStopRecordTenMin();
        timeTasks[TASK_RECORDTENMIN] = currentTime;
    }
}


/**
 * Executes all tasks giving them the current time.
 * Each task checks itself whether they need to be executed or not.
 */
void checkTasks() {
    /* Get the current time */
    currentTime = millis();

    /* Execute all the tasks */
    Task_readPressureAltTempSensor();
    Task_readGeigerCounter();
    Task_readCurrentSensor();
    Task_sendSensors();
    Task_record10Minutes();
}
