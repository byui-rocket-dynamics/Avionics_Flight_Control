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
#include <vector>
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
      std::vector<std::string> rowData; // Data located in a row in the .csv file
      std::string str, row;
      while(fin >> str)
      {
         row.clear();
         getline(fin, row);
         std::stringstream buffer(row);
         std::string temp;
         while(getline(buffer, temp, ','))
         {
            if(temp[0] == ' ')
               temp.erase(temp.begin());
            rowData.push_back(temp);
         }
         if(rowData[0] != "Time")
         {
            try{
            this->time.push(std::stoi(rowData[0]));
            int tempGYR[3];
            tempGYR[0] = std::stoi(rowData[1]);
            tempGYR[1] = std::stoi(rowData[2]);
            tempGYR[2] = std::stoi(rowData[3]);
            this->gyr.push(tempGYR);
            int tempVar[1];
            tempVar[0] = std::stoi(rowData[4]);
            this->mag.push(tempVar);
            this->alt.push(std::stof(rowData[5]));
            double tempVar2[1];
            // TODO: This causes a segfault, make it not do that.
            // tempVar2[0] = std::stod(rowData[6]);
            // this->temp.push(tempVar2);
            }
            catch(const std::invalid_argument& arg){
               printf("ERROR: Unable to parse data correctly!\n");
            }
         }
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
