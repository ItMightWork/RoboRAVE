
#include "motor_handler.h"

#define PHASE_PINL 10 //Phase pin for left motor
#define PHASE_PINR 11 //Phase pin for right motor

		//1 = left motor
		//2 = right motor
		//motor_handler - using = motorMove(strengthPerc, side);
		//-% = back, +% = forw, 0 = stop;

void * pilot_main(void *args){
		
		wiringPiSetup();
		
		int pwmPin19 = 19; 
		int pwmPin33 = 33;
		
		pinMode(PHASE_PINL, OUTPUT);	//Left motor phase pin setup
		pinMode(PHASE_PINR, OUTPUT);	//Right motor phase pin setup
		pinMode(pwmPin19, PWM_OUTPUT);	//Left motor enable pin setup (PWM)
		pinMode(pwmPin33, PWM_OUTPUT);	//Right motor enable pin setup (PWM)
	

	return NULL;
}