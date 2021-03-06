# Avionics_Flight_Control
The software here is made to read sensors, analyze data, and deploy the parachute on the BYUI Rocket.

## How to compile via Linux ##
There are two ways to compile.

The following is for compiling on the raspberry pi for the actual launch program.
~~~
make launch
~~~

The following is for compiling for testing on both the raspberry pi and any computer
~~~
make sim TYPE='SIMULATION'
~~~

## What Needs To Be Done ##
*If you complete one of these tasks, please mark it off and move it to the bottom of the list. If you are currently working on one of these, add your github username, surrounded by astrisks, after the task and remove it when it is done. Be sure to commit the README file with the claimed and the commit message "Claimed Task" BEFORE you start working on the task.*
- [ ] Logic for deploying drogue chute
- [ ] Logic for deploying main chute
- [ ] Logic for knowing when rocket is on the ground
- [ ] Logic for saving the data to a file in collectData()
- [ ] Logic for saving data in the logs queue to a file in logData() - *philkkw*
- [ ] Logic for pushing data into the logs queue in log()
- [ ] Logic for saving the flight summary in saveSummary()
- [ ] Logic for updating flight summary variables (and figure out best place to do that)
- [ ] Create simple way to test the program not on the raspberry pi (simple simulation) - *Amulek1416*
- [ ] Make logic for sending data to the ground
- [ ] Algorithm to filter the data when going moch speeds
- [x] Have collectData() update struct FlightData data
- [x] Create and join threads
- [x] Logic for when the rocket has been launched
- [x] Delay to compensate for moch speeds
- [x] Create ability to compile not just on the raspberry pi

> *Example on how to edit the file to check off tasks and add username:*
~~~
 Markup: - [ ] An uncompleted task not being worked on
         - [ ] An uncompleted task being worked on -  *my_username* 
         - [x] A completed task
~~~

## Graphic of Program ##
~~~
    +------+
    |main()|
    +--+---+
       |
       v
+------+--------+
|flightProgram() |                +-------------+
+-------+-------+                 |   THREAD    |
        |                     +-->------------------+
        |                     |   |collectData()|   |
    +---+---+       +------+  |   +-------------+   |
    |start()+------>+init()+--+                     +----------------------------------------------------------------------+
    +---+---+       +------+  |   +----------+      |                                                                      |
        |                     |   |  THREAD  |      |                                                                      |
        |                     +-->------------------+                                                                      |
        |                         |sendData()|                                                                             |
        |                         +----------+                                                                             |
        |                                                                                                                  |
        |                        +--------------+  +------------+  +------+  +-----+  +-------------+  +----------+  +-----v-------+
        +------------------------+deployDrogue()+--+deployMain()+--+land()+--+end()+--+saveSummary()+--+saveLogs()+--+joinThreads()|
                                 +--------------+  +------------+  +------+  +-----+  +-------------+  +----------+  +-------------+
~~~
