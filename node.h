//
// Created by gabby on 23/11/2024.
//
#include "moves.h"
#ifndef UNTITLED1_NODE_H
#define UNTITLED1_NODE_H
typedef struct s_node
{
    struct s_node ** children;    // Pointeur vers le tableau des enfants du nœud
    struct s_node * parent;       // Pointeur vers le parent, pour retracer le chemin

    t_move mvt_for_access;        // Mouvement effectué pour atteindre cette position

    int cost;                     // Coût associé pour atteindre cette position
    int max_children;
    int num_children;             // Nombre d'enfants actuels (utile pour les parcours)

} t_node;
t_node* create_node(t_move mvt_for_access, int cost, int nb_children);
#endif //UNTITLED1_NODE_H
