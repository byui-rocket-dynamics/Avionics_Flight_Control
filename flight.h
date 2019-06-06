/********************************************
 * PROGRAM: Flight program for avionics 
 *          system for BYU-I Rocket Dynamics
 * 
 * AUTHORS: Zac Carico
 * 
 * SUMMARY: This file contains functions and 
 *          data structures that will be used 
 *          in the avionics system.
 * 
 * FORMAT RULES:  
 *          Tabs as spaces, 3 spaced indentation
 * ******************************************/

#ifndef FLIGHT_H
#define FLIGHT_H

// Distance (in ft) from gound that main parachute 
// will deploy.
#define BLOW_MAIN       1500 

// The size that the data container will start at.
// this is used to reduce overhead.
#define INIT_DATA_SIZE  500

// To determine the maximum size that the data 
// container can be. This is to not over fill memory.
#define MAX_SIZE        1000

// Paths to files
#define LOG_FILE        ""
#define SAVE_FILE       ""
#define SUMMARY_FILE    ""

//LIBRARIES
#include <deque>        // Data structure to store flight data
#include <queue>        // Data structure used for logging
#include <pthread.h>    // Used for handling the creation of threads
#include <semaphore.h>  // Used for making the program thread-safe
#include <stdio.h>

// Libraries for sensor data. One part is for 
// simulating. The other is for the actual program.
#ifdef SIMULATION
     // Libraries that will suppliment functions called
     //   for pi/sensor specific functions.
     #include "./simLibs/wiringPi.h"
     #include "./simLibs/sensorBMPSim.h"
#else
     #include <wiringPi.h>
     extern "C" {
          //header file for the C code to run BMP180
          #include "./sensorCode/bmp180-master/bmp180dev3.h" 
          #include "./sensorCode/lsm303dlhc-master/lsm303dlhc.h"
     }
#endif

/*********************************
 * Structure containing all data 
 *    that will be recorded during 
 *    flight.
 * *******************************/
struct FlightData
{
   int time;
   int* gyr;
   int* acc;
   int* mag; 
   float alt;
};

/*********************************
 * Structure used for creating log
 *    messages. Can be used to 
 *    collect specific data points
 *    durring flight.
 * *******************************/
struct LogInfo
{
   char* tag;
   char* log;
};

struct FlightSummary
{
   int flightTime;
   float maxAlt;
   int maxSpeed;
};

/////////////////////
// GLOBAL VARIABLES//
/////////////////////

// Structures that need to be thread safe
std::deque<struct FlightData> data;
std::queue<struct LogInfo> logs;

// Structures that don't need to be thread safe
bool inFlight;
bool startOfFlight;
struct FlightSummary summary;

// ID's for each thread
pthread_t dataID;
pthread_t logID;
pthread_t saveID;
pthread_t flightID;

//Semaphores to keep data thread-safe
sem_t dataSem;
sem_t logSem;

// FUNCTIONS
//    More info in flight.cpp
void flightProgram();
void init();
void start();

void *getData(void* p);
void *logData(void* p);
void *saveData(void *p);
void log(char *tag, char *message);

void end();
void saveSummary();

/********************************************
 * MAIN: Main function for program
 * ******************************************/

int main()
{
   flightProgram();
   return 0;
}
#endif /*FLIGHT_H*/