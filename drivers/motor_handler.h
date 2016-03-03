

#include <wiringPi.h>
#include <softPwm.h>
							

		//1 = left motor
		//2 = right motor
		//pwmPin = 12 - left motor - 19 on odroid
		//pwmPin = 23 - right motor - 33 on odroid
		//softPwmWrite - max value = 1024
		//1 - phase 2 - enable



int motorMove (int strengthPerc, int motorNum, int pPinL, int pPinR) {

	int pwmPin;
		
		////FORWARD////
		if (strengthPerc > 0) {
					
			
			////LEFT MOTOR////
			if (motorNum == 1) {
			
				pwmPin = 12; 
					
				digitalWrite(pPinL, LOW);  					//Phase 

				softPwmWrite(pwmPin, strengthPerc);   		//Enable 
			}

			///RIGHT MOTOR////
			else if (motorNum == 2) {

				pwmPin = 23;

				digitalWrite(pPinR, LOW);					//Phase

			    softPwmWrite(pwmPin, strengthPerc); 		//Enable
			}

			////BOTH MOTORS////
			else if (motorNum == 3) {

				//LEFT//
					pwmPin = 12; 
					
				digitalWrite(pPinL, LOW);  					//Phase

				softPwmWrite(pwmPin, strengthPerc);   		//Enable 

				//RIGHT//
					pwmPin = 23;

				digitalWrite(pPinR, LOW);					//Phase

			    softPwmWrite(pwmPin, strengthPerc); 		//Enable
			}
		}
	
		////REVERSE////		
		else if (strengthPerc < 0) {

						
			////LEFT MOTOR////			
			if (motorNum == 1) {

				pwmPin = 12;					
				
				digitalWrite(pPinL, HIGH);  				//Phase 
				
				softPwmWrite(pwmPin, strengthPerc);   		//Enable
			}

			////RIGHT MOTOR////
			else if (motorNum == 2) {

				pwmPin = 23;
				
				digitalWrite(pPinR, HIGH);					//Phase
				
				softPwmWrite(pwmPin, strengthPerc); 		//Enable
			}

			////BOTH MOTORS////
			else if (motorNum == 3) {

				//LEFT//
					pwmPin = 12; 
					
				digitalWrite(pPinL, HIGH);  				//Phase 

				softPwmWrite(pwmPin, strengthPerc);   		//Enable 

				//RIGHT//
					pwmPin = 23;

				digitalWrite(pPinR, HIGH);					//Phase

			    softPwmWrite(pwmPin, strengthPerc); 		//Enable
			}

		}

		////BRAKE////		
		else if (strengthPerc == 0) {

			int strengthPerc = 0;

			////LEFT MOTOR////
			if (motorNum == 1) {

				pwmPin = 12; 				
				
				digitalWrite(pPinL, LOW);  					//Phase - can be anything 
				
				softPwmWrite(pwmPin, strengthPerc);   		//Enable  - must be 0
			}

			////RIGHT MOTOR////
			else if (motorNum == 2) {

				pwmPin = 23;
				
				digitalWrite(pPinR, LOW);					//Phase - can be anything 

				softPwmWrite(pwmPin, strengthPerc); 		//Enable - must be 0
			}

			////BOTH MOTORS////
			else if (motorNum == 3) {

				//LEFT//
					pwmPin = 12; 
					
				digitalWrite(pPinL, LOW);  					//Phase 

				softPwmWrite(pwmPin, strengthPerc);   		//Enable 

				//RIGHT//
					pwmPin = 23;

				digitalWrite(pPinR, LOW);					//Phase

			    softPwmWrite(pwmPin, strengthPerc); 		//Enable
			}
		}

	return 0;
}




