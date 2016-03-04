#include "odometer.c"
#include "motor_handler.h"

#define PI 3.14;
#define TURNAXLE 10; //cm


int robotTurn(int angle) {

	float circlePerimeter;
	float turnDistance;
	
	lisbusb_device_handle * device = init_mouse();
	int x,y;
	x = 0;
	y = 0;

	int global_x, global_y;
	global_x = 0;
	global_y = 0;
	bool jump = 1;



	if (angle > 0) {													//Turning right
		
		circlePerimeter = 2*TURNAXLE*PI;  								//Get distance to travel and compare to optical sensor output 
		turnDistance = (circlePerimeter/360)*angle;

		motorMove(50, 1);												//Start motors to be able to read distance values from mouse sensor
		motorMove(-50, 2);
		
		while (jump) {

			get_distance(device, &x, &y);								//Optical sensor input
			global_x += x;
			global_y += y;

			if (x == turnDistance || y == turnDistance) {				//Compare turnDistance with optical sensor values 
				jump = false;
			}
		}																


		motorMove(0, 3);												//After reaching desired angle stop both motors
		jump = true;
		x = 0;
		y = 0;
 		
	}
    
    else if (angle < 0) {												//Turning left

    	circlePerimeter = 2*TURNAXLE*PI;  								//Get distance to travel and compare to optical sensor output 
		turnDistance = (circlePerimeter/360)*abs(angle);

		motorMove(-50, 1);												//Start motors to be able to read distance values from mouse sensor
		motorMove(50, 2);

		while (jump) {

			get_distance(device, &x, &y);								//Optical sensor input
			global_x += x;
			global_y += y;

			if (x == -turnDistance || y == -turnDistance) {				//Compare turnDistance with optical sensor values 
				jump = false;
			}
		}																


		motorMove(0, 3);												//After reaching desired angle stop both motors
		jump = true;
		x = 0;
		y = 0;
    }
	
	return 0;	

}