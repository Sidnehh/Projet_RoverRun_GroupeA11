#ifndef QUEUE_H
#define QUEUE_H

#include "tree.h"

/**
 * @brief Structure for the queue of t_node pointers
 */
typedef struct s_queue
{
    t_node **values; // Array of pointers to t_node
    int size;        // Maximum size of the queue
    int last;        // Index of the last element
    int first;       // Index of the first element
} t_queue;

// Function prototypes
t_queue createQueue(int size);
void enqueue(t_queue *p_queue, t_node *node);
t_node *dequeue(t_queue *p_queue);

#endif // QUEUE_H

