// Created by SURFACE on 12/11/2024.

#include "loc.h"
#include "moves.h"
#include "map.h"
#include "stack.h"
#include "node.h"
#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

// Structures requises à l'utilisation des arbres

// Définition d'un nœud dans l'arbre, représentant un mouvement spécifique



// Définition de la structure de l'arbre 
typedef struct s_tree
{
    t_node* root;   // Pointeur vers la racine de l'arbre
} t_tree;


// Fonctions de gestion de l'arbre (prototypes)


// Initialise un nœud avec une position, un mouvement et un coût
t_node* create_node(t_move mvt_for_access, int cost, int nb_children);

// Libère la mémoire allouée pour un nœud et ses enfants
void free_tree(t_node* root);

// Ajoute un enfant à un nœud parent
void add_child(t_node* parent, t_node* child);

//Alloue la mémoire d'un arbre selon nombre de mouvements requis
t_tree* allocate_tree(int nb_movements);

t_move adjustMoveBasedOnTerrain(t_move chosen_move, t_position current_position, t_map map);
//Crée une structure de n enfants à un noeud
void build_from_node(t_node* node, int nb_children, t_localisation curr_loc, t_map map, int branch_moves[], int total_moves);

// Crée un arbre
t_tree* create_tree(int nb_movements, t_map map, t_localisation start_loc);

t_node* find_min_cost_node(t_node* cur_node, t_node* min_node);


// Recherche le chemin depuis la racine vers la feuille de valeur minimale d'un arbre
t_node* getMinRec(t_tree* tree);

// Recherche le chemin depuis la racine vers la feuille de valeur minimale d'un arbre
void afficher_arbre(t_node* root);
t_stack findMinCostPath(t_tree* tree);
#endif // UNTITLED1_TREE_H
