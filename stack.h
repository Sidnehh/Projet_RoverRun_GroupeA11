#ifndef UNTITLED1_STACK_H
#define UNTITLED1_STACK_H

#include "node.h"

/**
 * @brief Structure for the stack of t_node pointers
 */
typedef struct s_stack
{
    t_node **values; // Array of pointers to t_node
    int size;        // Maximum size of the stack
    int nbElts;      // Number of elements currently in the stack
} t_stack;

// Function prototypes
t_stack createStack(int size);
void push(t_stack *p_stack, t_node *node);
t_node *pop(t_stack *p_stack);
t_node *top(t_stack stack);

#endif //UNTITLED1_STACK_H

