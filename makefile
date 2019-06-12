
################################################
#
#
#
#
################################################

# COMILER OPTIONS GO HERE
CFLAGS = -pthread

SIM_PATH = ./simLibs/
LAUNCH_PATH = ./sensorCode/

TYPE = LAUNCH

# BUILD SIMULATION LAUNCH PROG
sim: wiringPi.o sensorBMPSim.o flight.o
	g++ -o sim wiringPi.o sensorBMPSim.o flight.o $(CFLAGS)

	 
# FILES
wiringPi.o: $(SIM_PATH)wiringPi.h $(SIM_PATH)wiringPi.cpp
	g++ -c $(SIM_PATH)wiringPi.cpp

sensorBMPSim.o: $(SIM_PATH)sensorBMPSim.h $(SIM_PATH)sensorBMPSim.cpp
	g++ -c $(SIM_PATH)sensorBMPSim.cpp

flight.o: flight.h flight.cpp
	g++ -c flight.cpp -D $(TYPE) 

# RULES
clean:
	rm sim launch *.o


# BUILDING THE LAUNCH PROGRAM
launch: 
	g++ -o launch flight.o -pthread