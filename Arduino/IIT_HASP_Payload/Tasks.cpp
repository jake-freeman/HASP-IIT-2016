#include "Tasks.h"
// #include <Adafruit_BMP085.h>
// #include <Adafruit_INA219.h>
// #include <TMP006.h>
// #include <HUMIDITY_HIH6130.h>
// #include <MPU6050.h>
// #include <MS5803_I2C.h>
// #include <copernicus.h>
#include <Wire.h>
#include <MS5803_I2C.h>

/* Stores the last moment in which each sensor was sampled */
unsigned long timeTasks[NUMBER_OF_TASKS];

/* Stores the last sampled value of each sensor */
unsigned long sensorValues[NUMBER_OF_SENSORS];

/* Stores the current time in milliseconds */
unsigned long currentTime;

/* Temperature sensor */
//extern uint8_t temp_I2CAddress;

/* Pressure sensor */
//extern Adafruit_BMP085 bmp;
extern MS5803 pressure_sensor;


/* Current sensor */
//extern Adafruit_INA219 ina219;

/**
 * Task to read the Temperature sensor 1
 */
void Task_readTemp1Sensor(){

    if( currentTime - timeTasks[TASK_TEMP1] > TASKPERIOD_TEMP1 ){
        // sensorValues[SENSARRAY_TEMP1] = readDieTempC(temp_I2CAddress);
        // timeTasks[TASK_TEMP1] = currentTime;
    }
}


/**
 * Task to read the Light sensor
 */
void Task_readLightSensor(){

    if( currentTime - timeTasks[TASK_LIGHT] > TASKPERIOD_LIGHT ){
        // sensorValues[SENSARRAY_LIGHT] = analogRead(LIGHTSENSOR_PIN)/2;
        // timeTasks[TASK_LIGHT] = currentTime;
    }
}


/**
 * Task to read the Pressure sensor
 */
void Task_readPressureSensor(){

    if( currentTime - timeTasks[TASK_PRESSURE] > TASKPERIOD_PRESSURE ){
        // sensorValues[SENSARRAY_PRESSURE] = bmp.readPressure();
        // timeTasks[TASK_PRESSURE] = currentTime;
        // To measure to higher degrees of precision use the following sensor settings:
        // ADC_256
        // ADC_512
        // ADC_1024
        // ADC_2048
        // ADC_4096

        // Read temperature from the sensor in deg C. This operation takes about
        //temperature_c = pressure_sensor.getTemperature(CELSIUS, ADC_512);

        // Read temperature from the sensor in deg F. Converting
        // to Fahrenheit is not internal to the pressure_sensor.
        // Additional math is done to convert a Celsius reading.
        //temperature_f = pressure_sensor.getTemperature(FAHRENHEIT, ADC_512);

        // Read pressure from the sensor in mbar.
        Serial.println("Read Pressure!");
        Serial.flush();
        double pressure_abs = pressure_sensor.getPressure(ADC_4096);
        sensorValues[TASK_PRESSURE] = pressure_abs;
        timeTasks[TASK_PRESSURE] = currentTime;
        Serial.println(pressure_abs);
        Serial.flush();

        // Let's do something interesting with our data.

        // Convert abs pressure with the help of altitude into relative pressure
        // This is used in Weather stations.
        //pressure_relative = sealevel(pressure_abs, base_altitude);

        // Taking our baseline pressure at the beginning we can find an approximate
        // change in altitude based on the differences in pressure.
        //altitude_delta = altitude(pressure_abs , pressure_baseline);

        // Report values via UART
        // COM_serial->print("Temperature C = ");
        // COM_serial->println(temperature_c);
        //
        // COM_serial->print("Temperature F = ");
        // COM_serial->println(temperature_f);
        //
        // COM_serial->print("Pressure abs (mbar)= ");
        // COM_serial->println(pressure_abs);
        //
        // COM_serial->print("Pressure relative (mbar)= ");
        // COM_serial->println(pressure_relative);
        //
        // COM_serial->print("Altitude change (m) = ");
        // COM_serial->println(altitude_delta);
    }
}


/**
 * Task to read the Humidity and secondary Temperature sensor
 */
void Task_readHumidity_Temp2Sensor(){

    unsigned int H_dat, T_dat;

    if( currentTime - timeTasks[TASK_HUMIDITY_TEMP2] > TASKPERIOD_HUMIDITY_TEMP2 ){
        // fetch_humidity_temperature(&H_dat, &T_dat);
        // sensorValues[SENSARRAY_HUMIDITY] = H_dat * 6.10e-3;
        // sensorValues[SENSARRAY_TEMP2] = T_dat * 1.007e-2 - 40.0;
        // timeTasks[TASK_HUMIDITY_TEMP2] = currentTime;
    }
}


/**
 * Task to read the current sensor for Arduino
 */
void Task_readArduinoCurrentSensor(){

    if( currentTime - timeTasks[TASK_CURRENT1] > TASKPERIOD_CURRENT1 ){
        // sensorValues[SENSARRAY_CURRENT1] = ina219.getCurrent_mA(5);
        // timeTasks[TASK_CURRENT1] = currentTime;
    }
}


// /**
//  * Task to read the current sensor for the VCO
//  */
// void Task_readVCOCurrentSensor(){
//
//     if( currentTime - timeTasks[TASK_CURRENT2] > TASKPERIOD_CURRENT2 ){
//         sensorValues[SENSARRAY_CURRENT2] = ina219.getCurrent_mA(-1);
//         timeTasks[TASK_CURRENT2] = currentTime;
//     }
// }



/**
 * Task to send the sensors over Serial communication
 */
void Task_sendSensors(){

    if( currentTime - timeTasks[TASK_SENDSENSORS] > TASKPERIOD_SENDSENSORS ){
        // COMM_sendSensors(sensorValues, currentTime);
        // timeTasks[TASK_SENDSENSORS] = currentTime;
    }
}


/**
 * Task for the HackHD to record 10 minutes. Stops the camera when the 10 minutes have passed.
 */
void Task_record10Minutes(){

    /* If the recording is not active, exit the function */
    if( !HackHD_getHackHDRecordTenMin() ){
        //timeTasks[TASK_RECORDTENMIN] = currentTime;
        //return;
    }

    if( currentTime - timeTasks[TASK_RECORDTENMIN] > TASKPERIOD_RECORDTENMIN ){
        //HackHD_startStopRecordTenMin();
        //timeTasks[TASK_RECORDTENMIN] = currentTime;
    }
}



/**
 * Task to control the VCO autotune mode.
 */
// void Task_VCOAutotune(){
//
//     /* If autotune mode is not active, exit the function */
//     if( !VCO_getAutotune() ){
//         timeTasks[TASK_VCOAUTOTUNE] = currentTime;
//         return;
//     }
//
//     if( currentTime - timeTasks[TASK_VCOAUTOTUNE] > TASKPERIOD_VCOAUTOTUNE ){
//         VCO_nextState();
//         timeTasks[TASK_VCOAUTOTUNE] = currentTime;
//     }
// }


/**
 * Executes all tasks giving them the current time.
 * Each task checks itself whether they need to be executed or not.
 */
void checkTasks(){

    /* Get the current time */
    currentTime = millis();

    /* Execute all the tasks */
    Task_readTemp1Sensor();
    Task_readLightSensor();
    Task_readPressureSensor();
    Task_readHumidity_Temp2Sensor();
    Task_readArduinoCurrentSensor();
    //Task_readVCOCurrentSensor();
    Task_sendSensors();
    //Task_record10Minutes();
    //Task_VCOAutotune();
}
