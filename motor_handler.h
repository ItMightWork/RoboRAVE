
#include "WiringPi.h"

#define PHASE_PINL 10
#define PHASE_PINR 11

	//1 = left motor
	//2 = right motor
	//pwmPin = 19 - left
	//pwmPin = 33 - right

int motorMoveForw (int strengthPerc, int motorNum) {

	wiringPiSetup();
	int pwmPin;
	int motorSpeed = (int) (10.24*strengthPerc);
	
	while(1) {	
		////LEFT MOTOR////

		if (motorNum = 1) {
			
			pwmPin = 19; 
					
			pinMode(PHASE_PINL, OUTPUT);
			digitalWrite(PHASE_PINL, LOW);  //Phase 

			pinMode(pmwPin, PWM_OUTPUT);
			pwmWrite(pwmPin, motorSpeed);   //Enable
		}

		///RIGHT MOTOR////

		else if (motorNum = 2) {

			pwmPin = 33;

			pinMode(PHASE_PINR, OUTPUT);
			digitalWrite(PHASE_PINR, LOW);	//Phase

			pinMode(pwmPin, PWM_OUTPUT);
			pwmWrite(pwmPinm, motorSpeed); //Enable
		}
	}
	return 0;
}




