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

// Time (in seconds) to delay checking for apogee.
// This is to keep the rocket from blowing chutes
// during burnout.
#define MACH_DELAY      10

// Values to signify how much of a change needs to
// happen for the rocket to determine that it is 
// currently launching. 
#define ACC             20 // THIS NEEDS TO BE CHANGED TO A CORRECT VALUE
#define ALT             20 // THIS NEEDS TO BE CHANGED TO A CORRECT VALUE

// Paths to files
#define LOG_FILE        "" // THIS NEEDS TO BE CHANGED TO A CORRECT VALUE
#define SAVE_FILE       "" // THIS NEEDS TO BE CHANGED TO A CORRECT VALUE
#define SUMMARY_FILE    "" // THIS NEEDS TO BE CHANGED TO A CORRECT VALUE

//LIBRARIES
#include <queue>        // Data structure used for logging
#include <pthread.h>    // Used for handling the creation of threads
#include <semaphore.h>  // Used for making the program thread-safe
#include <stdio.h>      // Used for using printf() function
#include <fstream>      // Used for reading and writting to files

// Libraries for sensor data. One part is for 
// simulating. The other is for the actual program.
#ifdef SIMULATION
   // Libraries that will suppliment functions called
   //   for pi/sensor specific functions.
   #include "./simLibs/wiringPi.h"
   #include "./simLibs/sensorBMPSim.h"
   #define SIM
   SimData simData;
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

/*********************************
 * Structure used for creating a 
 *    basic summary of the flight.
 * *******************************/
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
//    (CURRENTLY NONE)

// Structures that don't need to be thread safe
struct FlightData data;
std::queue<struct LogInfo> logs;
struct FlightSummary summary;
bool inFlight;
bool startOfFlight;

// ID's for each thread
pthread_t collectDataID;
pthread_t sendDataID;

//Semaphores to keep data thread-safe
//   (CURRENTLY NONE)

// FUNCTIONS
//    More info in flight.cpp
void flightProgram();
void init();
void start();
void deployDrogue();
void deployMain();
void land();

void *collectData(void* p);
void *sendData(void * p);
void log(char *tag, char *message);

void end();
void saveSummary();
void logData();
/********************************************
 * MAIN: Main function for program
 * ******************************************/
#ifdef SIM
int main()
{
   char *fileName;
   simData.loadTestData(fileName);
   flightProgram();
   return 0;
}
#else
int main()
{
   flightProgram();
   return 0;
}
#endif /* #ifdef SIM */

#endif /*FLIGHT_H*/