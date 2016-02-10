//#include "camera_driver.h"

void get_color_field(int minimum, int maximum, unsigned char quantized_image[], unsigned char target[], int lenght){		//returns field of bools, true for color in tolerance
	for (int i=0; i<lenght; ++i){
		if (minimum <= quantized_image[i] && quantized_image[i] <= maximum){
			target[i] = 1;
		} else {
			target[i] = 0;
		}
	}
}

void color_quantization(int lenght, unsigned char raw_image[lenght*3],unsigned char quantized_image[lenght]){			//converts image to 27 colours
	unsigned char R,G,B;
	for (int pixel=0; pixel<lenght; ++pixel){
		R = 3*raw_image[pixel*3]/256.0;
		G = 3*raw_image[pixel*3+1]/256.0;
		B = 3*raw_image[pixel*3+2]/256.0;
		quantized_image[pixel] = R + 3*G + 9*B;
	}
}

/*
#include <stdio.h>
int main(){
	int image_size[] = {360,240};
	int image_lenght = image_size[0]*image_size[1];
	unsigned char raw_image[image_lenght*3];
	unsigned char quantized_image[image_lenght];
	//while(1){
		//getimage(image_lenght*3,raw_image);
		raw_image[0] = 255;
		raw_image[1] = 255;
		raw_image[2] = 255;
		color_quantization(image_lenght,raw_image,quantized_image);
		printf("%d\n", quantized_image[0]);


	//}
	return 0;
}*/



void * cv_main(void *args){
	//printf("cv initialized\n");
	// do stuff
	
	return NULL;
}