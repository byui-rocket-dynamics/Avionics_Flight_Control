/****************************************************
 * FILE: wiringPiSim.h
 * AUTHOR: Zac Carico
 * LAST MODIFIED: 4/8/19
 * 
 * DESC: This file is used to emulate the wiringPi.h 
 *       library. Really it is just to have empty 
 *       functions one can use to test raspberry pi 
 *       programs on any computer. This is very useful 
 *       to test logic of functions. 
 * 
 *       Eventually one can just edit a variable from 
 *       this file to point to a file containing test 
 *       data to be read from certain pins and one 
 *       pointing to a folder containing files to write 
 *       pin output to.
 * **************************************************/

// #define PATH_TO_DATA_FOLDER   "File path here"
// #define PATH_TO_WRITE_FOLDER  "File path here"

#ifndef PATH_TO_DATA_FOLDER 
   #define PATH_TO_DATA_FOLDER false
#endif

#ifndef PATH_TO_WRITE_FOLDER 
   #define PATH_WRITE_FOLDER false
#endif

#define OUTPUT true
#define INPUT  false

#define HIGH   true
#define LOW    false

// CORE FUNCTIONS
void pinMode(int pin, int mode);
void pullUpDnControl(int pin, int pud);
void digitalWrite(int pin, int value);
void pwmWrite(int pin, int value);
void analogWrite(int pin, int value);
int digitalRead(int pin);
int analogRead(int pin);

// SETUP FUNCTIONS
int wiringPiSetup(void);
int wiringPiSetupGpio(void);
int wiringPiSetupPhys(void);
int wiringPiSetupSys(void);

// // PI SPECIFIC FUNCTIONS
// void digitalWriteByte(int value);
// void pwmSetMode(int mode);
// void pwmSetRange(unsigned int range);
// void pwmSetClock(int divisor);
// void piBoardRev(void);
// void wpiPinToGpio(int wPiPin);
// void physPinToGpio(int phydsPin);
// void setPadDrive(int group, int value);

// TIMING FUNCTIONS
unsigned int millis(void);
unsigned int micros(void);
void delay(unsigned int howLong);
void delayMicroseconds(unsigned int howLong);

// // PRIOTITY, INTERRUPT, THREADS
// int piHiPri(int priority);
// int waitForInterrupt(int pin, int timeOut); 
// int wiringPiISR(int pin, int edgeType, void (*function)(void));
// int piThreadCreate(char *name);
// void piLock(int keyNum);
// void piUnlock(int keyNum);

// // SERIAL FUNCTIONS
// int serialOpen(char *device, int baud);
// void serialClose(int fd);
// void serialPutchar(int fd, unsigned char c);
// void serialPuts(int fd, char *s);
// void serialPrintf(int fd, char *message);
// int serialDataAvail(int fd);
// int serialGetchar(int fd);
// void serialFlush(int fd);

// // SPI FUNCTIONS
// int wiringPiSPISetup(int channel, int speed);
// int wiringpiSPIDataRW(int channel, unsigned char *data, int len);

// //I2C FUNCTIONS
// int wiringPiI2CSetup(int devID);
// int wiringPiI2CRead(int fd);
// int wiringPiI2CWrite(int fd, int data);
// int wiringPiI2CWriteReg8(int fd, int reg, int data);
// int wiringPiI2CWriteReg16(int fd, int reg, int data);
// int wiringPiI2CRead8(int fd, int reg);
// int wiringPiI2CRead16(int fd, int reg);

// // SHIFT LIBRARY
// uint8_t shiftIn(uint8_t dPin, uint8_t cPin, uint8_t order);
// void shiftOut(uint8_t dPin, uint8_t cPin, uint8_t order, uint8_t val);

// // SOFTWARE PWM
// int softPwmCreate(int pin, int initialValue, int pwmRange);
// void doftPwmWrite(int pin, int value);

// // SOFTWARE TONE
// int softToneCreate(int pin);
// void softToneWrite(int pin, int freq);