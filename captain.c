#include <stdio.h>
#include <pthread.h>

#define MAP_SIZE 10

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int robot_posX = MAP_SIZE/2;
int robot_posY = MAP_SIZE/2;
int robot_direction;

int map_size = MAP_SIZE;
unsigned char map[MAP_SIZE][MAP_SIZE];

#include "nav_comp.h"
#include "cv.h"
#include "pilot.h"


int main(){
	pthread_t nav_comp;
	pthread_t cv;
	pthread_t pilot;

	pthread_create(&nav_comp, NULL, nav_comp_main, 0);
	pthread_create(&cv, NULL, cv_main, 0);
	pthread_create(&pilot, NULL, pilot_main, 0);


	pthread_join(nav_comp,NULL);
	pthread_join(cv,NULL);
	pthread_join(pilot,NULL);

}