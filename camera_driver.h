#include "WiringPi.h" //TODO

// [START] --------------- PIN DEFINITIONS -------------------

#define WE_PIN 0
#define RRST_PIN 0
#define RCLK_PIN 0

int data_pins[] = {0, 0, 0, 0, 0, 0, 0, 0};

// [END] --------------- PIN DEFINITIONS -------------------



void get_image(int image_size, unsigned char image[]) {
	wiringPiSetup();

	// pin init
	for (int i=0; i<8; ++i){
		pinMode(data_pins[i], INPUT);
	}

	pinMode(WE_PIN, OUTPUT);
	digitalWrite(WE_PIN, 1);
	pinMode(RRST_PIN, OUTPUT);
	digitalWrite(RRST_PIN, 1);
	pinMode(RCLK_PIN, OUTPUT);
	digitalWrite(RCLK_PIN, 0);

	// send image from camera to FIFO - TODO
	digitalWrite(WE_PIN, 0);		// enable write

	// get image from FIFO
	digitalWrite(WE_PIN, 1);		// disable write while reading
	
	digitalWrite(RRST_PIN, 0);		// reset read pointer to 0
	digitalWrite(RCLK_PIN, 0);
	digitalWrite(RCLK_PIN, 1);
	digitalWrite(RCLK_PIN, 0);
	digitalWrite(RRST_PIN, 1);

	for (int i=0, i<image_size, ++i){		// read bytes from FIFO
		digitalWrite(RCLK_PIN, 1);
		image[i] = 0;
		for (int b=0; b < 8; ++b)
			if (digitalRead(data_pins[b]))
				image[i] |= 1 << b;
		digitalWrite(RCLK_PIN, 0);
	}

}