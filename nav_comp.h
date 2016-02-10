#include "queue.h"
#include <unistd.h>
//
//	NavComp
//
//	0 - unvisited
//	1 - free space
//	2 - line
//	3 - fire
//	4 - wall
//

void * nav_comp_main(void *arg){
	// Initialization
	pthread_mutex_lock(&lock);
	int local_map_size = map_size;
	pthread_mutex_unlock(&lock);
	unsigned char local_map[local_map_size][local_map_size];

	char directions[4][2] = {{0,-1}, {1,0}, {0,1}, {-1,0}};

	int start_posX, start_posY;
	int x,y;
	int new_x,new_y;
	int found_unvisited[2] = {-1,-1};
	int found_target[2] = {-1,-1};
	int pos_changed = 1;

	int queue_value, map_value;

	queue *Q = create_queue(5*local_map_size);

	// Main task
	//while (1){
		do {
			pthread_mutex_lock(&lock);						// Check if position changed else wait for it to change
			if (start_posX == robot_posX && start_posY == robot_posY){
				pos_changed = 0;
			} else {
				pos_changed = 1;
				start_posX = robot_posX;
				start_posY = robot_posY;
			}
			pthread_mutex_unlock(&lock);
			sleep(0.01);
		} while (pos_changed == 0);

		pthread_mutex_lock(&lock);							// update local map
		for (int i=0; i<local_map_size; ++i){
			for (int k=0; k<local_map_size; ++k){
				local_map[i][k] = map[i][k];
			}
		}
		pthread_mutex_unlock(&lock);


		queue_value = start_posX;							// Insert start position into queue
		queue_value |= start_posY<<15;
		add_item(Q,queue_value);
		map[start_posY][start_posX] |= 1<<7;
		
		// BFS loop
		while (Q->size > 0){
			queue_value = pick_item(Q);						// Load tested node
			x = queue_value & 0x7fff;
			y = queue_value & (0x7fff<<15);

			map_value = local_map[y][x];					// Check node if wanted 
			map_value &= 0x7f;
			if (map_value == 0 && found_unvisited[0] < 0){	// Write down first unexplored node
				found_unvisited[0] = x;
				found_unvisited[1] = y;
			}
			if (map_value == 3){
				found_target[0] = x;						// Target found! 
				found_target[1] = y;
				break;
			}

			for (int i=0; i<4; ++i){						// Explore node's neightbours
				new_x = x + directions[i][0];
				new_y = y + directions[i][1];
				//printf("testing %d %d\n", new_x,new_y);
				if (new_x >= 0 && new_x < local_map_size && new_y >= 0 && new_y < local_map_size){		// If coords are valid
					//printf("passed\n");
					map_value = local_map[new_y][new_x];
					printf("%d\n", (map_value & (1<<7)));
					if (!(map_value & (1<<7))){				// If node is not discovered
						if ((map_value & 0x1f) < 4){		// If node is not wall
							queue_value = new_x;
							queue_value |= new_y<<15;
							add_item(Q, queue_value);		// Add node to queue
						}
					}
				}
			}
		}

	printf("unvisited: %d %d\n", found_unvisited[0],found_unvisited[1]);
	printf("target: %d %d\n", found_target[0],found_target[1]);
	//}

	return NULL;
}
