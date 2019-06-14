/********************************************
 * PROGRAM: Flight program for avionics 
 *          system for BYU-I Rocket Dynamics
 * 
 * AUTHORS: Zac Carico
 * 
 * SUMMARY: File contains definitions for 
 *          functions in "flight.h". The 
 *          program uses threads to take full 
 *          advantage of all CPU cores that 
 *          the raspberry pi 3B+/3A+ has. 
 *          
 *          Please be sure to run many tests 
 *          before commiting any changes. 
 *          Threads can be tricky. Seek 
 *          additional assistance as needed.
 * 
 * FORMAT RULES:  
 *          Tabs as spaces, 3 spaced indentation
 * ******************************************/

// LIBRARIES
#include "flight.h"

/********************************************
 * INIT: This is the function that needs to 
 *    be called first in the "start" function.
 *    This function sets all the defaults for 
 *    variables and initializes the semaphores 
 *    and mutexes.
 * ******************************************/
void init()
{
   // Structures to initialize for threading
   //    (CURRENTLY NONE)

   // Flight variables
   inFlight = false;
   startOfFlight = false;

   // Data Structures
   //    (CURRENTLY NONE)

   // Other Structures
   //    (CURRENTLY NONE)
}

/********************************************
 * START: The function handles starting the 
 *    program by creating threads.
 * ******************************************/
void start()
{
   init();
   pthread_create(&collectDataID, NULL, collectData, NULL);
   pthread_create(&sendDataID, NULL, sendData, NULL);
   int tempACC = *data.acc;
   float tempALT = data.alt;
   while((*data.acc - tempACC < ACC) && (data.alt - tempALT < ALT))
   {
     log("i", "Waiting for launch\n");
     delayMicroseconds(10);
   }
   inFlight = true;
   startOfFlight = true;
}

/********************************************
 * END: Joins the threads together, and calls
 *    any functions that may need to be called
 *    at the end of flight. Eventually the 
 *    rocket will try to send out its GPS 
 *    location here so we can easily find it.
 * ******************************************/
void end()
{
   logData();
   saveSummary();
   pthread_join(collectDataID, NULL);
   pthread_join(sendDataID, NULL);
}

/********************************************
 * SAVE_SUMMARY: At the end of the flight, 
 *    the data in "summary" structure should 
 *    be saved
 * ******************************************/
void saveSummary()
{
   // TODO: Save the contents in the "summary"
   //       data structure to a file.
}

/********************************************
 * LOG_DATA: This will save the logs in the 
 *    queue to a file at the end of the flight.
 * ******************************************/
void logData()
{
   // TODO: Save log info to a log file
}

///////////// CONCURRENT FUNCTIONS /////////////

/********************************************
 * GET_DATA: Function collects data from the 
 *    sensors and saves them to a file. These
 *    two steps aren't threaded, otherwise we
 *    would eventually overflow memory.
 * ******************************************/
void *collectData(void* p)
{  
   int fd = bmpSetup(); // Used for reading from sensors
   // TODO: Open file here
   while(!inFlight)
   {
      data.alt = getAltitude(fd);
      readACC(data.acc);
   }

   while(inFlight)
   {
      readACC(data.acc);
      readMAG(data.mag);
      readGYR(data.gyr);
      data.alt = getAltitude(fd);
      
      // TODO: Save data to file here
      // Format: "<time>, <gyr>, <mag>, <alt>, <temp>\n"

   }
   // TODO: Close file here

}

/********************************************
 * SEND_DATA: Function sends data to the ground
 *    durring flight.
 * ******************************************/
void *sendData(void *p)
{
   // This can be left empty until the 
   // communications system is complete.
}

/********************************************
 * LOG: Way to interface with the "logs" data
 *    structure. This function pushes logs to 
 *    the structure.
 * 
 *    TAGS: 
 *          "i" = "info"      "e" = "error"
 *        "wtf" = "What a terrible failure"
 * ******************************************/
void log(char* tag, char* message)
{
   // TODO: Write logic to push data onto logs queue
}

/********************************************
 * FLIGHT_PROGRAM: TBD
 * ******************************************/
void flightProgram()
{
   log("i", "Program Started");
   start();

   // So we don't accidently deploy chutes too early
   delayMicroseconds(MACH_DELAY); 

   deployDrogue();
   deployMain();
   land();

   end();
}

/********************************************
 * DEPLOY_DROGUE: Logic to decide when to 
 *    deploy the drogue chute.
 * ******************************************/
void deployDrogue()
{
   log("i", "Starting deployDrogue()");
   // TODO: Write logic

   log("i", "Drogue parachute deployed");
}

/********************************************
 * DEPLOY_MAIN: Logic to decide when to deploy
 *    the main parachute.
 * ******************************************/
void deployMain()
{
   log("i", "Starting deployMain()");
   // TODO: Write logic

   log("i", "Main parachute deployed");
}

/********************************************
 * LAND: Program to decide when the rocket has
 *    landed and to stop collecting data. 
 * ******************************************/
void land()
{
   log("i", "Starting land()");
   // TODO: Write logic

   log("i", "Landed");
}