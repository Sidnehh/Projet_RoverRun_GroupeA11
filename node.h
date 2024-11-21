//
// Created by gabby on 21/11/2024.
//

#ifndef UNTITLED1_NODE_H
#define UNTITLED1_NODE_H

#include "node.h"
#include "stdio.h"
#include "loc.h"
#include "moves.h"
#include "stdlib.h"

typedef struct s_node
{
    struct s_node **children; // Tableau de pointeurs vers les enfants
    struct s_node *parent;        // Pointeur vers le parent
    t_localisation loc;          // Position de MARC après ce mouvement
    t_move movement;              // Mouvement effectué pour atteindre cette position
    int cost;
    int num_children;
    int max_children;
    int total_cost;
} t_node;
// Initialise un nœud avec une position, un mouvement et un coût
t_node* create_node(t_localisation loc, t_move mov, int cost, int max_children,t_node* parent);

// Libère la mémoire allouée pour un nœud et ses enfants
void free_node(t_node* node);


// Ajoute un enfant à un nœud parent
void add_child(t_node* parent, t_node* child);
#endif //UNTITLED1_NODE_H
