#include <stdlib.h>
#include <assert.h>
#include "stack.h"

/**
 * @brief Function to create a stack of t_node pointers
 * @param size : the size of the stack
 * @return the stack
 */
t_stack createStack(int size)
{
    // The size of the stack must be positive
    assert(size > 0);
    t_stack stack;
    stack.size = size;
    stack.nbElts = 0;
    stack.values = (t_node **)malloc(size * sizeof(t_node *)); // Pointeurs vers t_node
    return stack;
}

/**
 * @brief Function to push a t_node pointer onto the stack
 * @param stack : the stack
 * @param node : the pointer to push
 * @return none
 */
void push(t_stack *p_stack, t_node *node)
{
    // The stack must not be full
    assert(p_stack->nbElts < p_stack->size);
    p_stack->values[p_stack->nbElts] = node;
    p_stack->nbElts++;
    return;
}

/**
 * @brief Function to pop a t_node pointer from the stack
 * @param stack : the stack
 * @return the popped pointer
 */
t_node *pop(t_stack *p_stack)
{
    // The stack must not be empty
    assert(p_stack->nbElts > 0);
    p_stack->nbElts--;
    return p_stack->values[p_stack->nbElts];
}

/**
 * @brief Function to get the top t_node pointer of the stack without removing it
 * @param stack : the stack
 * @return the top pointer
 */
t_node *top(t_stack stack)
{
    // The stack must not be empty
    assert(stack.nbElts > 0);
    return stack.values[stack.nbElts - 1];
}
