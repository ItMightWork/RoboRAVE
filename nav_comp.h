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

	int start_posX = -1;
	int start_posY = -1;
	int x, y, new_x, new_y;
	int found_unvisited[2] = {-1,-1};
	int found_target[2] = {-1,-1};
	int pos_changed = 1;
	int path_lenght, direction;

	int queue_value, map_value;

	queue *Q = create_queue(5*local_map_size);

	// ----- Main task -----
	//while (1){
		do {		// Update data
			pthread_mutex_lock(&lock);						// Check if position changed else wait for the change
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

		pthread_mutex_lock(&lock);							// Update local map
		for (int i=0; i<local_map_size; ++i){
			for (int k=0; k<local_map_size; ++k){
				local_map[i][k] = map[i][k];
			}
		}
		pthread_mutex_unlock(&lock);
		// Update complete!


		local_map[1][1] = 4;
		local_map[3][6] = 4;
		local_map[4][6] = 4;
		local_map[5][6] = 3;

		found_target[0] = -1;								// Clear found
		found_target[1] = -1;
		found_unvisited[0] = -1;
		found_unvisited[1] = -1;

		while (pick_item(Q) != -1){}						// Clear queue

		queue_value = start_posX;							// Insert start position into queue
		queue_value |= start_posY<<15;						// queue_value = 00 000000000000000 000000000000000
		add_item(Q,queue_value);							//				 dir    y coord         x coord

		local_map[start_posY][start_posX] |= 1<<7;			// Flag start node as visited
															// map[y][x] = 0  00  00000
															//  	  visited dir object

		// BFS loop
		while (Q->size > 0){
			queue_value = pick_item(Q);						// Load tested node
			x = queue_value & 0x7fff;
			y = (queue_value>>15) & 0x7fff;

			local_map[y][x] |= (queue_value>>30)<<5;		// Write down source direction

			map_value = local_map[y][x] & 0x1f;				// Check node if wanted 
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

				if (new_x >= 0 && new_x < local_map_size && new_y >= 0 && new_y < local_map_size){		// If coords are valid
					map_value = local_map[new_y][new_x];
					if ((map_value>>7) == 0){					// If node is not discovered
						if ((map_value & 0x1f) < 4){			// If node is not wall
							queue_value = new_x;
							queue_value |= new_y<<15;
							queue_value |= ((i+2)%4)<<30;
							add_item(Q, queue_value);			// Add node to queue
						}
						local_map[new_y][new_x] |= 1<<7;	// Flag node as visited
					}
				}
			}
		}

/*
		printf("    0 1 2 3 4 5 6 7 8 9\n");
		for (int y = 0; y < local_map_size; ++y)
		{
			printf("%d | ", y);
			for (int x = 0; x < local_map_size; ++x)
			{
				printf("%d ", (local_map[y][x]) & 0x1f);
			}
			printf("\n");
		}
		printf("\n");
*/

		direction = 0;
		path_lenght = 0;
		if (found_target[0] != -1 || found_unvisited[0] != -1){						// If found path
			x = (found_target[0] != -1) ? found_target[0] : found_unvisited[0];		// Select target coords
			y = (found_target[1] != -1) ? found_target[1] : found_unvisited[1];

			new_x = x;
			new_y = y;
			while (!(start_posX == new_x && start_posY == new_y)){					// Count path lenght to start
				path_lenght++;
				direction = (local_map[new_y][new_x]>>5) & 0x3;
				new_x += directions[direction][0];
				new_y += directions[direction][1];
			}

			char path[path_lenght];										// Create path array
			for (int i = path_lenght-1; i >= 0; i--){					// Fill path array
				direction = (local_map[y][x]>>5) & 0x3;
				path[i] = (direction+2)%4;
				x += directions[direction][0];
				y += directions[direction][1];
			}

			printf("path: ");
			for (int i=0; i<path_lenght; i++){ printf("%d ", path[i]); }
			printf("\n");
		}

		printf("lenght: %d\n", path_lenght);
		printf("unvisited: %d %d\n", found_unvisited[0],found_unvisited[1]);
		printf("target: %d %d\n", found_target[0],found_target[1]);
	//}

	return NULL;
}
