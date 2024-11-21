#include <stdlib.h>
#include <assert.h>
#include "queue'.h"

/**
 * @brief Function to create a queue of t_node pointers
 * @param size : the size of the queue
 * @return the queue
 */
t_queue createQueue(int size)
{
    // The size of the queue must be positive
    assert(size > 0);
    t_queue queue;
    queue.size = size;
    queue.first = 0;
    queue.last = 0;
    queue.values = (t_node **)malloc(size * sizeof(t_node *)); // Pointeurs vers t_node
    return queue;
}

/**
 * @brief Function to enqueue a t_node pointer
 * @param queue : the queue
 * @param node : the pointer to enqueue
 * @return none
 */
void enqueue(t_queue *p_queue, t_node *node)
{
    // The queue must not be full
    assert((p_queue->last - p_queue->first) < p_queue->size);
    p_queue->values[p_queue->last % p_queue->size] = node;
    p_queue->last++;
    return;
}

/**
 * @brief Function to dequeue a t_node pointer
 * @param queue : the queue
 * @return the dequeued pointer
 */
t_node *dequeue(t_queue *p_queue)
{
    // The queue must not be empty
    assert(p_queue->last != p_queue->first);
    t_node *node = p_queue->values[p_queue->first % p_queue->size];
    p_queue->first++;
    return node;
}
