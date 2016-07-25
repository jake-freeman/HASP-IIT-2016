#ifndef TASKS_H
#define TASKS_H


/*********************************/
/************ INCLUDES ***********/
/*********************************/

#include "Comm.h"


/************************************/
/************* DEFINES **************/
/************************************/

#define NUMBER_OF_TASKS               5

#define TASK_PRESSURE                 0
#define TASK_GEIGER                   1
#define TASK_RECORDTENMIN             2
#define TASK_CURRENT                  3
#define TASK_SENDSENSORS              4

#define TASKPERIOD_PRESSURE           1000
#define TASKPERIOD_GEIGER             1000
#define TASKPERIOD_RECORDTENMIN     600000
#define TASKPERIOD_CURRENT            1000
#define TASKPERIOD_SENDSENSORS        1000


/***************************************/
/********** VARIABLES/OBJECTS **********/
/***************************************/

//extern int geiger_count; //set up int to counter number of events from geiger


/*******************************/
/********** FUNCTIONS **********/
/*******************************/

void checkTasks();

#endif
