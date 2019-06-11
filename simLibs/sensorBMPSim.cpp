#include "sensorBMPSim.h"

void close(int fd)   { return;   }
int bmpSetup()       { return 0; }
void enableIMU()     { return;   }

void readMAG(int *m) { m = simData.getMAG(); }
void readACC(int *a) { a = simData.getACC(); }
void readGYR(int *g) { g = simData.getGYR(); }
double getAltitude(int fd)                   { return simData.getALT(); }
void bmp_GetTemperature(int fd, double *temp){ temp = simData.getTEMP(); }

