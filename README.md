# Avionics_Flight_Control
The software here is made to read sensors, analyze data, and deploy the parachute on the BYUI Rocket.

## What Needs To Be Done ##
*If you complete one of these tasks, please mark it off and move it to the bottom of the list. If you are currently working on one of these, add your github username in front of the task surrounded by astrisks and remove it when it is done.*
- [ ] Logic for deploying drogue chute
- [ ] Logic for deploysing main chute
- [ ] Logic for knowing when rocket is on the ground
- [ ] Logic for saving the data to a file in collectData()
- [ ] Logic for saving data in the logs queue to a file in logData()
- [ ] Logic for pushing data into the logs queue in log()
- [ ] Logic for saving the flight summary in saveSummary()
- [ ] Logic for updating flight summary variables (and figure out best place to do that)
- [ ] Create simple way to test the program not on the raspberry pi (simple simulation)
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
         - [ ] *my_username* An uncompleted task being worked on
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
|flightProgram()|                 +-------------+
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
