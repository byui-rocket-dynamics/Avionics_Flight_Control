/***********************************************
 * FILE: sensorPiSim.h
 * AUTHOR: Zac Carico
 * LAST MODIFIED: 4/9/19
 * 
 * DESC: Contains the functions that are found
 *       in "bmp180dev3.h" and "lsm303dlhc.h" 
 *       that are used by the avionics system
 *       program. Add on to this as needed.
 * 
 *       Eventually this will be where test data
 *       will be given to the program to help
 *       sumulate a flight.
 * *********************************************/

// Functions
void close(int fd);
void enableIMU();
void readMAG(int *m);
void readACC(int *a);
void readGYR(int *g);
void bmp_GetTemperature(int fd, double *temp);
int bmpSetup();
double getAltitude(int fd);
