#include <libusb.h>

#include "tools.c"

#define VENDOR_ID		0x413c
#define PRODUCT_ID		0x3012
#define INTERFACE 		0

#define REG_AVERAGE_PIXEL	0x09

libusb_device_handle * init_mouse(){
	libusb_init(NULL);
	libusb_device_handle * device = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);	// create device
	libusb_set_auto_detach_kernel_driver(device, 1);		// set auto-detach
	libusb_claim_interface(device, INTERFACE);				// claim interface
	return device;
}


int read_register(libusb_device_handle * device, int address, unsigned char * result){
	return libusb_control_transfer(device, 0xC0, 0x01, 0x0000, address, result, 0x0001, 0);		// C0 01 00 00 xx 00 01 00
}

int get_surface_color(libusb_device_handle * device){
	unsigned char result = 0;
	read_register(device, REG_AVERAGE_PIXEL, &result);
	return (int) result;
}


void get_distance(libusb_device_handle * device, int * x, int * y){		// A1 01 00 01 00 00 03 00
	unsigned char buffer[3];
	libusb_control_transfer(device, 0xA1, 0x01, 0x0100, 0x0000, buffer, 0x0003, 0);
	*x = get_int_from_twos_complement(buffer[1],8);
	*y = get_int_from_twos_complement(buffer[2],8);
}

int close_mouse(libusb_device_handle * device){
	libusb_release_interface(device, INTERFACE);			// release claimed interface
	libusb_close(device);		// close device
	libusb_exit(NULL);			// deinit libusb
}

int get_configuration(libusb_device_handle * device){		// 80 08 00 00 00 00 01 00
	unsigned char buffer = 0;
	libusb_control_transfer(device, 0x80, 0x08, 0x0000, 0x0000, &buffer, 0x0001, 0);
	return (int) buffer;
}


// Example:
/*
void main(){
	libusb_device_handle * device = init_mouse();
	int x,y;

	int global_x, global_y;
	global_x = 0;
	global_y = 0;
	while (1){
		get_distance(device, &x, &y);
		global_x += x;
		global_y += y;
		printf("color: %d | x = %d, y = %d\n",get_surface_color(device),global_x,global_y);
	}

	close_mouse(device);

}
*/