#include "wiringPi.h"

// CORE FUNCTIONS
void pinMode(int pin, int mode)
{
   
}

void pullUpDnControl(int pin, int pud)
{

}

void digitalWrite(int pin, int value)
{
   if(PATH_WRITE_FOLDER)
   {

   }
}

void pwmWrite(int pin, int value)
{
   if(PATH_WRITE_FOLDER)
   {

   }
}

void analogWrite(int pin, int value)
{
   if(PATH_WRITE_FOLDER)
   {

   }
}

int digitalRead(int pin)
{
   int x = 0;
   if(PATH_TO_DATA_FOLDER)
   {

   }
   return x;
}

int analogRead(int pin)
{
   int x = 0;
   if(PATH_TO_DATA_FOLDER)
   {

   }
   return x;
}


// SETUP FUNCTIONS
int wiringPiSetup(void)
{
   return 0;
}

int wiringPiSetupGpio(void)
{
   return 0;
}

int wiringPiSetupPhys(void)
{
   return 0;
}

int wiringPiSetupSys(void)
{
   return 0;
}

// TIMING FUNCTIONS
unsigned int millis(void)
{
   return 0;
}

unsigned int micros(void)
{
   return 0;
}

void delay(unsigned int howLong)
{

}

void delayMicroseconds(unsigned int howLong)
{

}