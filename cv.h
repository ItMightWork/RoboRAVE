void color_quantization(int lenght, unsigned char raw_image[lenght*3],unsigned char quantized_image[lenght]){			//converts image to 27 colours
	unsigned char R,G,B;
	for (int pixel=0; pixel<lenght; ++pixel){
		R = 3*raw_image[pixel*3+2]/256.0;
		G = 3*raw_image[pixel*3+1]/256.0;
		B = 3*raw_image[pixel*3]/256.0;
		quantized_image[pixel] = R + 3*G + 9*B;
	}
}

void dequantize(int lenght, unsigned char source[lenght], unsigned char dequantized_image[lenght*3]){
	for (int i=0; i<lenght; ++i){
		dequantized_image[3*i] = 256*(source[i]/9)/3;
		dequantized_image[3*i+1] = 256*(source[i]%9)/9;
		dequantized_image[3*i+2] = 256*((source[i]%9)%3)/3;
	}
}


void color_quantization8(int lenght, unsigned char raw_image[lenght*3],unsigned char quantized_image[lenght]){			//converts image to 8 colours
	unsigned char R,G,B;
	for (int pixel=0; pixel<lenght; ++pixel){
		R = 2*raw_image[pixel*3+2]/256.0;
		G = 2*raw_image[pixel*3+1]/256.0;
		B = 2*raw_image[pixel*3]/256.0;
		quantized_image[pixel] = R + 2*G + 4*B;
	}
}

void dequantize8(int lenght, unsigned char source[lenght], unsigned char dequantized_image[lenght*3]){
	for (int i=0; i<lenght; ++i){
		dequantized_image[3*i] = 256*(source[i]/4)/2;
		dequantized_image[3*i+1] = 256*(source[i]%4)/4;
		dequantized_image[3*i+2] = 256*((source[i]%4)%2)/2;
	}
}




int detect_vertical_lines(int color, int line_width[2], int image_size[2], unsigned char source_image[image_size[0]*image_size[1]], int result_start, int result[image_size[0]*image_size[1]*2]){
	int start, tested_last, found;																	// detects vertical lines
	found = 0;

	for (int y=0; y<image_size[1]; ++y){
		start = 0;
		tested_last = -1;
		for(int end=0; end < image_size[0]; ++end){
			if (source_image[y*image_size[0] + end] == color && tested_last != color){
				start = end;
			}
			if (source_image[y*image_size[0] + end] != color && tested_last == color){
				if (end-start > line_width[0] && end-start < line_width[1]){
					result[result_start + found*2] = start + (end-start)/2;
					result[result_start + found*2+1] = y;
					found++;
					start = end;
				}
			}
			tested_last = source_image[y*image_size[0] + end];
		}
	}
	return found;
}

int detect_horizontal_lines(int color, int line_width[2], int image_size[2], unsigned char source_image[image_size[0]*image_size[1]], int result_start, int result[image_size[0]*image_size[1]*2]){
	int start, tested_last, found;																	// detects hotizontal lines
	found = 0;

	for (int x=0; x<image_size[0]; ++x){
		start = 0;
		tested_last = -1;
		for(int end=0; end < image_size[1]; ++end){
			if (source_image[end*image_size[0] + x] == color && tested_last != color){
				start = end;
			}
			if (source_image[end*image_size[0] + x] != color && tested_last == color){
				if (end-start > line_width[0] && end-start < line_width[1]){
					result[result_start*2 + found*2+1] = start + (end-start)/2;
					result[result_start*2 + found*2] = x;
					found++;
					start = end;
				}
			}
			tested_last = source_image[end*image_size[0] + x];
		}
	}
	return found;
}

void show_points(int lenght, int points[lenght*2],int image_size[2], unsigned char target[image_size[0]*image_size[1]*3], int color[3]){
	for (int i=0; i<lenght; ++i){
		target[3*(points[i*2+1]*image_size[0] + points[i*2])] = color[0];
		target[3*(points[i*2+1]*image_size[0] + points[i*2])+1] = color[1];
		target[3*(points[i*2+1]*image_size[0] + points[i*2])+2] = color[2];
	}
}


#include <opencv/cv.h>
#include <opencv/highgui.h>


void * cv_main(void *args){
	int c;
	CvCapture* camera = cvCaptureFromCAM(0);
	IplImage* captured_image;

	cvNamedWindow("Source",0); // create window
	cvNamedWindow("Result",0); // create window

	int image_size[2] = {640,480};
	int image_lenght = image_size[0] * image_size[1];

	unsigned char image[image_lenght];

	int line_width[2] = {7,50};		// min, max line width

	int red[3] = {0,0,255};
	int blue[3] = {255,0,0};

	int found;
	int found_lines[image_lenght*2];

	// Main loop
	while (1) {
		captured_image = cvQueryFrame(camera); 																	// Get frame

		if(captured_image != 0){
			cvShowImage("Source", captured_image); 																// Show source frame
			cvErode(captured_image, captured_image, NULL, 1);
			color_quantization(captured_image->imageSize/3, captured_image->imageData, image);					// Quantize image for easier work
			/*
			for (int i=0; i<image_lenght*3; ++i){
				captured_image->imageData[i] = 0;
			}*/

			dequantize(image_lenght,image,captured_image->imageData);

			for (int i=0; i<found; ++i){
				found_lines[i*2] = 0;
				found_lines[i*2+1] = 0;
			}

			found = detect_vertical_lines(0,line_width,image_size,image,0,found_lines);
			found = found + detect_horizontal_lines(0,line_width,image_size,image,found,found_lines);

			show_points(found,found_lines,image_size,captured_image->imageData,red);
			for (int i=0; i<found; ++i){
				found_lines[i*2] = 0;
				found_lines[i*2+1] = 0;
			}

			found = detect_horizontal_lines(2,line_width,image_size,image,0,found_lines);

			show_points(found,found_lines,image_size,captured_image->imageData,blue);




			cvShowImage("Result", captured_image); // show frame
		}
		c = cvWaitKey(10); // wait 10 ms or for key stroke
		if(c == 27)
			break; // if ESC, break and quit
	}
	/* clean up */
	cvReleaseCapture( &camera );
	cvDestroyWindow("Source");
	cvDestroyWindow("Result");
	
	return NULL;
}