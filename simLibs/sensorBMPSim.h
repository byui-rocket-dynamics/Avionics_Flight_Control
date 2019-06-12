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

#include <queue>
#include <fstream>
#include <string>
#include <sstream>

/**********************************************
* DATA_POINT: Simple class to hold data points
***********************************************/
class DataPoint
{
private:
   int time;
   int *gyr;
   int *acc;
   int *mag;
   double *temp;
   float alt;
public:
   DataPoint(int time, int *gyr, 
      int *acc, int *mag, double* temp, float alt)
   {
      this->time  = time;
      this->gyr   = gyr;
      this->acc   = acc;
      this->mag   = mag;
      this->alt   = alt;
      this->temp  = temp;
   }
   int getTime()     { return this->time; }
   int* getGYR()     { return this->gyr;  }
   int* getACC()     { return this->acc;  }
   int* getMAG()     { return this->mag;  }
   float getALT()    { return this->alt;  }
   double* getTEMP() { return this->temp; }
};

class SimData
{
private:
   std::queue<int> time;
   std::queue<int*> gyr;
   std::queue<int*> acc;
   std::queue<int*> mag;
   std::queue<double*> temp; 
   std::queue<float> alt;
public:
   void load(DataPoint p) { time.push(p.getTime());
                            gyr.push(p.getGYR());
                            acc.push(p.getACC());
                            mag.push(p.getMAG());
                            alt.push(p.getALT());
                            temp.push(p.getTEMP()); }

   int* getMAG() {int* temp = mag.front(); 
                  mag.pop(); 
                  return temp; }
   int* getGYR() {int* temp = gyr.front(); 
                  gyr.pop(); 
                  return temp; }
   int* getACC() {int* temp = acc.front(); 
                  acc.pop(); 
                  return temp; }
   int getTime() {int temp = time.front(); 
                  time.pop(); 
                  return temp; }
   float getALT() {float temp = alt.front(); 
                  alt.pop(); 
                  return temp; }
   double* getTEMP() {double* temp = this->temp.front();
                      this->temp.pop();
                      return temp;}
   
   void loadTestData(char* fileName)
   {
      std::fstream fin;
      fin.open(fileName);
      std::string str, row;
      while(fin >> str)
      {
         row.clear();
         getline(fin, row);
         std::stringstream buffer(row);
         int temp = 0;
         //TODO: Continue by filling variables with data in stringstream
      }
      fin.close();
   }
};

// extern variable located in flight.h file
extern SimData simData;

// Functions
void close(int fd);
void enableIMU();
void readMAG(int *m);
void readACC(int *a);
void readGYR(int *g);
void bmp_GetTemperature(int fd, double *temp);
int bmpSetup();
double getAltitude(int fd);
