#include <stdlib.h>

typedef struct Queue {
        int capacity;
        int size;
        int first;
        int last;
        int *elements;
} queue;



queue * create_queue(int size){
        queue *Q;                                           // Create a Queue
        Q = (queue *)malloc(sizeof(queue));

        Q->elements = (int *)malloc(sizeof(int)*size);      // Initialise its properties
        Q->size = 0;
        Q->capacity = size;
        Q->first = 0;
        Q->last = -1;

        return Q;                                           // Return the pointer
}

int pick_item(queue *Q){
    if(Q->size == 0) {                      // If Queue size is zero then it is empty. So we cannot pop.
            return -1;
    } else {                                // Removing an element is equivalent to incrementing index of first by one.
        int result = Q->first;
        Q->size--;
        Q->first++;

        if(Q->first == Q->capacity) {       // As we fill elements in circular fashion.
                Q->first=0;
        }

        return Q->elements[result];
    }
}

int add_item(queue *Q, int element) {
    if (Q->size == Q->capacity) {
        return -1;
    } else {
        Q->size++;
        Q->last = Q->last + 1;

        if(Q->last == Q->capacity) {        // As we fill the queue in circular fashion.
                Q->last = 0;
        }

        Q->elements[Q->last] = element;     // Insert the element in its last side.
    }
    return 1;
}

// Usage:
/*
#include <stdio.h>
int main()
{
        queue *Q = create_queue(5);
        add_item(Q,1);
        add_item(Q,2);
        add_item(Q,3);
        add_item(Q,4);
        printf("first element is %d\n",pick_item(Q));
        add_item(Q,5);
        pick_item(Q);
        add_item(Q,6);
        printf("first element is %d\n",pick_item(Q));
}
*/