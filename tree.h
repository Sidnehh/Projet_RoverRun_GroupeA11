// Created by SURFACE on 12/11/2024.


#include "moves.h"
#include <time.h>
#include "map.h"
#include "stack.h"
#include "queue.h"
#include "node.h"

#ifndef UNTITLED1_TREE_H

// Définition de la structure de l'arbre 
typedef struct s_tree
{
    t_node* root;   // Pointeur vers la racine de l'arbre
    int nb_movements ;
} t_tree;


// Fonctions de gestion de l'arbre (prototypes)


//Alloue la mémoire d'un arbre selon nombre de mouvements requis
t_tree* allocate_tree(int nb_movements);

//Crée une structure de n enfants à un noeud
void build_from_node(t_node* parent, int nb_children, t_map map);
void find_min_path(t_tree* tree);
t_node* find_min_cost_node(t_tree* tree);

t_stack find_min_cost_path(t_node* min_node);
t_tree* create_tree(int nb_movements, t_map map);

#endif // UNTITLED1_TREE_H
