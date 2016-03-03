#include <stdio.h>
#include <wiringPiI2C.h>
#include <unistd.h>
#include <math.h>

#define MAG_CONFIGURATION_REGISTER_A	0
#define MAG_CONFIGURATION_REGISTER_B	1
#define MAG_MODE_REGISTER				2
#define MAG_DATA_X_MSB_REGISTER			3
#define MAG_DATA_X_LSB_REGISTER			4
#define MAG_DATA_Y_MSB_REGISTER			5
#define MAG_DATA_Y_LSB_REGISTER			6
#define MAG_DATA_Z_MSB_REGISTER			7
#define MAG_DATA_Z_LSB_REGISTER			8
#define MAG_STATUS_REGISTER				9
#define MAG_IDENTIFICATION_REGISTER_A	10
#define MAG_IDENTIFICATION_REGISTER_B	11
#define MAG_IDENTIFICATION_REGISTER_C	12
#define MAG_ADDRESS 0x1E

// HMC5883L datasheet: https://www.adafruit.com/datasheets/HMC5883L_3-Axis_Digital_Compass_IC.pdf


int mag_init(){										// initializes I2C device, returns device handler
	int device = wiringPiI2CSetup(MAG_ADDRESS);
	if (device == -1){
		printf("Can't setup the I2C device\n");
	}
	return device;
}


int mag_set_config(int device, int output_rate, int sampling, int mode){		// sets measurement configuration
	int success = -1;
	if (output_rate >= 0 && output_rate <= 6 && 
		sampling >= 0 && sampling <= 3 &&
		mode >= 0 && sampling <= 2){
		success = wiringPiI2CWriteReg8(device, MAG_CONFIGURATION_REGISTER_A, (sampling << 5) | (output_rate << 2) | mode);
	}
	return success;
}

int mag_get_raw_config(int device){			// returns a raw value of configuration register A
	return wiringPiI2CReadReg8(device, MAG_CONFIGURATION_REGISTER_A);
}

int mag_set_mode(int device, int mode){		// sets measuring mode: 0 - continuous measurement, 1 - single measurement, 2 - idle
	int success = -1;
	if (mode >= 0 && mode <= 2){
		success = wiringPiI2CWriteReg8(device, MAG_MODE_REGISTER, mode);
	}
	return success;
}

int mag_get_mode(int device){					// returns measuring mode
	int mode = (wiringPiI2CReadReg8(device, MAG_MODE_REGISTER) << 1) >> 1;
	if ((mode >> 1) == 1){
		return 2;
	}
	return mode;
}

int mag_set_gain(int device, int gain){		// sets device gain
	int success = -1;
	if (gain >= 0 && gain <= 7){
		success = wiringPiI2CWriteReg8(device, MAG_CONFIGURATION_REGISTER_B, gain << 5);
	}
	return success;
}

int mag_get_gain(int device){					// returns device gain
	return wiringPiI2CReadReg8(device, MAG_CONFIGURATION_REGISTER_B) >> 5;
}

int mag_get_status(int device){					// returns device status
	return wiringPiI2CReadReg8(device, MAG_STATUS_REGISTER);
}

int mag_get_axes(int device, float* x, float* y, float* z){				// returns measured values in form of Values struct
	values val;															// NOT WORKING CORRECTLY
	///*
	*x = (wiringPiI2CReadReg8(device, MAG_DATA_X_MSB_REGISTER) << 8) | wiringPiI2CReadReg8(device, MAG_DATA_X_LSB_REGISTER);
	*y = (wiringPiI2CReadReg8(device, MAG_DATA_Y_MSB_REGISTER) << 8) | wiringPiI2CReadReg8(device, MAG_DATA_Y_LSB_REGISTER);
	*z = (wiringPiI2CReadReg8(device, MAG_DATA_Z_MSB_REGISTER) << 8) | wiringPiI2CReadReg8(device, MAG_DATA_Z_LSB_REGISTER);
	//*/
	/**x = wiringPiI2CReadReg16(device, MAG_DATA_X_MSB_REGISTER);
	*y = wiringPiI2CReadReg16(device, MAG_DATA_Y_MSB_REGISTER);
	*z = wiringPiI2CReadReg16(device, MAG_DATA_Z_MSB_REGISTER);*/
	*x *= 0.92;
	*y *= 0.92;
	*z *= 0.92;
	return 0;
}

float mag_get_planar_heading(int x, int y){				// NOT WORKING CORRECTLY
	float heading;
	if (y > 0){
		heading = 90 - atan2(y,x)*180/M_PI;
	} else if (y < 0){
		heading = 270 - atan2(y,x)*180/M_PI;
	} else {
		if (x < 0){
			heading = 180.0;
		} else {
			heading = 0.0;
		}
	}
	return heading;
}

/*
int main(){
	float x,y,z, heading;

	int device = mag_init();
	mag_set_mode(device,0);

	while (1){
		mag_get_axes(device, &x, &y, &z);
		heading = mag_get_planar_heading(x,y);
		printf("Heading: %f X: %f  Y: %f  Z: %f\n", heading, x, y, z);
		sleep(1);
	}

	return 0;
}*/