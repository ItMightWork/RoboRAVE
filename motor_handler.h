
#include "WiringPi.h"

#define PHASE_PINL 10 //Phase pin for left motor
#define PHASE_PINR 11 //Phase pin for right motor

	//1 = left motor
	//2 = right motor
	//pwmPin = 19 - left motor
	//pwmPin = 33 - right motor
	//pwmWrite - max value = 1024

int motorMove (int strengthPerc, int motorNum) {

	wiringPiSetup(); //Might be removed
	int pwmPin;
		
		////FORWARD////
		if (strengthPerc > 0) {

			int motorSpeed = (int) (10.24*strengthPerc);
			
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
		else if (strengthPerc < 0) {

			int motorSpeed = (int) abs(10.24*strengthPerc);
			
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
		else if (strengthPerc = 0) {

			int motorSpeed = 0;

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




