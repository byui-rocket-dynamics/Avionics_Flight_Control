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
   // Structures for threading
   sem_init(&dataSem, 0, 1);
   sem_init(&logSem, 0, 1);
   inFlight = false;
   startOfFlight = true;

   // Data Structures
   data.resize(INIT_DATA_SIZE);

   // Other Structures

}

/********************************************
 * START: The function handles starting the 
 *    program by creating threads.
 * ******************************************/
void start()
{
   init();
   pthread_create(&dataID, NULL, getData, NULL);
   pthread_create(&saveID, NULL, saveData, NULL);
   pthread_create(&logID, NULL, logData, NULL);
}

/********************************************
 * END: Joins the threads together, and calls
 *    any functions that may need to be called
 *    at the end of flight.
 * ******************************************/
void end()
{
   pthread_join(dataID, NULL);
   pthread_join(saveID, NULL);
   pthread_join(logID, NULL);
   saveSummary();
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

///////////// CONCURRENT THREADS /////////////

/********************************************
 * GET_DATA: Function collects data from the 
 *    sensors and adds them to the deque.
 * ******************************************/
void *getData(void* p)
{
   int buffer = 10;
   struct FlightData tData;
   
   int fd = bmpSetup(); // Used for reading from sensors

   while(inFlight)
   {
      // TODO: Figure out a way for function to run while
      //       it's waiting for the semaphore

      // Fill up tData with sensor data
      readACC(tData.acc);
      readMAG(tData.mag);
      readGYR(tData.gyr);
      tData.alt = getAltitude(fd);

      // Store data between sem functions. The
      //    sem functions are what make the 
      //    program thread safe. We don't want
      //    two threads editing the same info
      //    at the same time.
      sem_wait(&dataSem);
      data.push_front(tData);
      sem_post(&dataSem);
   }
}

/********************************************
 * LOG_DATA: When there is something on the 
 *    queue, the logData function will wakeup,
 *    save logs to a file, then go back asleep
 *    when the queue is empty.
 * ******************************************/
void *logData(void* p)
{
   // TODO: Save log info to a log file
}

/********************************************
 * LOG: Way to interface with the "logs" data
 *    structure. This function pushes logs to 
 *    the structure.
 * 
 *    TAGS: 
 *       (TODO: Create definitions for the tags)
 * ******************************************/
void log(char* tag, char* message)
{
   // TODO: Write logic to push data onto "logs" structure
}

/********************************************
 * SAVE_DATA: Save the data being processed 
 *    by "getData". 
 * ******************************************/
void *saveData(void *p)
{
   //TODO: Save data to a .csv file or something similar.
}

/********************************************
 * FLIGHT_PROGRAM: TBD
 * ******************************************/
void flightProgram()
{
   start();

   // TODO: Create flight logic here
   end();
}