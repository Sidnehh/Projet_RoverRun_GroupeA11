//
// Created by flasque on 19/10/2024.
//

#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include "stdio.h"
#include "moves.h"

/**
 * @brief Function to create a stack
 * @param size : the size of the stack
 * @return the stack
 */
t_stack createStack(int size)
{
    // the size of the stack must be positive
    assert(size > 0);
    t_stack stack;
    stack.size = size;
    stack.nbElts = 0;
    stack.values = (int *)malloc(size * sizeof(int));
    return stack;
}

/**
 * @brief Function to push a value in the stack
 * @param stack : the stack
 * @param value : the value to push
 * @return none
 */

void resize_stack(t_stack *p_stack) {
    int new_size = p_stack->size * 2; // Double la taille de la pile
    p_stack->values = (int *)realloc(p_stack->values, new_size * sizeof(int));
    if (p_stack->values == NULL) {
        printf("Erreur : impossible de redimensionner la pile.\n");
        exit(EXIT_FAILURE);
    }
    p_stack->size = new_size;
    printf("Pile redimensionnée à %d éléments.\n", new_size);
}
void push(t_stack *p_stack, int value) {
    if (p_stack->nbElts >= p_stack->size) {
        resize_stack(p_stack); // Redimensionne si nécessaire
    }
    p_stack->values[p_stack->nbElts] = value;
    p_stack->nbElts++;
}
/**
 * @brief Function to pop a value from the stack
 * @param stack : the stack
 * @return the value popped
 */
int pop(t_stack *p_stack)
{
    // the stack must not be empty
    assert(p_stack->nbElts > 0);
    p_stack->nbElts--;
    return p_stack->values[p_stack->nbElts];
}

/**
 * @brief Function to get the top value of the stack
 * @param stack : the stack
 * @return the top value
 */
int top(t_stack stack)
{
    // the stack must not be empty
    assert(stack.nbElts > 0);
    return stack.values[stack.nbElts - 1];
}
int isEmptyStack(t_stack s)
{
    return (s.nbElts == 0);
}

void displayStack(t_stack s)
{
    int size = s.nbElts;
    if (size==0)
    {
        printf("Pas de chemin");
    }
    for (int cpt = 0; cpt <size; cpt++)
    {
        printf("%s --> ", getMoveAsString(s.values[cpt]));
    }
    printf("\n");
    return;
}