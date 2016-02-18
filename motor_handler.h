
#include "WiringPi.h"

#define PHASE_PINL 10
#define PHASE_PINR 11

	//1 = left motor
	//2 = right motor
	//pwmPin = 19 - left
	//pwmPin = 33 - right

int motorMove (int strengthPerc, int motorNum) {

	wiringPiSetup();
	int pwmPin;
	int motorSpeed = (int) (10.24*strengthPerc);
	
		////FORWARD////

		if (motorSpeed > 0) {
			
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
	
		////REVERSE////
		
		else if (motorSpeed < 0) {

			motorSpeed = abs(motorSpeed);
			
			////LEFT MOTOR////
			
			if (motorNum = 1) {

				pwmPin = 19; 
					
				pinMode(PHASE_PINL, OUTPUT);
				digitalWrite(PHASE_PINL, HIGH);  //Phase 

				pinMode(pmwPin, PWM_OUTPUT);
				pwmWrite(pwmPin, motorSpeed);   //Enable
			}

			////RIGHT MOTOR////

			else if (motorNum = 2) {

				pwmPin = 33;

				pinMode(PHASE_PINR, OUTPUT);
				digitalWrite(PHASE_PINR, HIGH);	//Phase

				pinMode(pwmPin, PWM_OUTPUT);
				pwmWrite(pwmPinm, motorSpeed); //Enable
			}

		}

		////BRAKE////
		
		else {

			////LEFT MOTOR////

			if (motorNum = 1) {

				pwmPin = 19; 
					
				pinMode(PHASE_PINL, OUTPUT);
				digitalWrite(PHASE_PINL, LOW);  //Phase - can be anything 

				pinMode(pmwPin, PWM_OUTPUT);
				pwmWrite(pwmPin, motorSpeed);   //Enable  - must be 0
			}

			////RIGHT MOTOR////

			else if (motorNum = 2) {

				pwmPin = 33;

				pinMode(PHASE_PINR, OUTPUT);
				digitalWrite(PHASE_PINR, LOW);	//Phase - can be anything 

				pinMode(pwmPin, PWM_OUTPUT);
				pwmWrite(pwmPinm, motorSpeed); //Enable - must be 0
			}
		}

	return 0;
}




