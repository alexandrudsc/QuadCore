# README #

* This repository contains the source code for the software side of QuadCore's project for Electromobility

* The main branch contains:
1. the source code for the android app
2. the source code for the application running on the microcontroller

* * * QuadCore communication protocol (initial concept) * * * 
- digits 0 and 1 form the code of the message (EXAMPLE: code for battery: "01")
                  * TIME_ELAPSED = 0;
                  * BATTERY_STATUS = 1;
                  * CAR_SPEED = 2;
                  * DISTANCE = 3;
                  * WHEEL_LEFT_STATUS = 4;
                  * WHEEL_RIGHT_STATUS = 5;
                  * SENSOR_STATUS = 6;
- digits 2 and 3 forms the number for the battery level 
(EXAMPLE: code for battery level 45 out of 100: "0145"; code for battery level 5 out of 100: "0105")
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *