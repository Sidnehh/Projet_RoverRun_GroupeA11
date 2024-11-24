//
// Created by gabby on 23/11/2024.
//

#include "node.h"
#include <stdlib.h>
#include <stdio.h>
t_node* create_node(t_move mvt_for_access, int cost, int nb_children)
{
    t_node* new_node = (t_node*)malloc(sizeof(t_node));
    if (new_node == NULL)
    {
        printf("Erreur d'allocation mémoire pour un nœud\n");
        return NULL;
    }
    // Initialisation des valeurs du nœud
    new_node->mvt_for_access = mvt_for_access;
    new_node->cost = cost;
    new_node->num_children = 0;
    new_node->parent = NULL;
    new_node->children = (t_node**) malloc(nb_children*sizeof(t_node*));
    if (new_node->children==NULL)
    {
        printf("Erreur d'allocation en mémoire");
        free(new_node);
        return NULL;
    }
    return new_node;
}

