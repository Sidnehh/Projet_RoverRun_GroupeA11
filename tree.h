// Created by SURFACE on 12/11/2024.

#include "loc.h"
#include "moves.h"
#include "map.h"
#include "stack'.h"
#include "queue'.h"
#include "stack'.h"


#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H



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



// Définition de la structure de l'arbre 
typedef struct s_tree
{
    t_node* root;   // Pointeur vers la racine de l'arbre
    int nb_movements ;
} t_tree;


// Fonctions de gestion de l'arbre (prototypes)


// Initialise un nœud avec une position, un mouvement et un coût
t_node* create_node(t_localisation loc, t_move mov, int cost, int max_children,t_node* parent);

// Libère la mémoire allouée pour un nœud et ses enfants
void free_node(t_node* node);


// Ajoute un enfant à un nœud parent
void add_child(t_node* parent, t_node* child);

//Alloue la mémoire d'un arbre selon nombre de mouvements requis
t_tree* allocate_tree(int nb_movements);

//Crée une structure de n enfants à un noeud
void build_from_node(t_node* parent, int nb_children, t_map map);
void find_min_path(t_tree* tree);
t_node* find_min_cost_node(t_tree* tree);

t_stack find_min_cost_path(t_node* min_node);
t_tree* create_tree(int nb_movements, t_map map);

#endif // UNTITLED1_TREE_H
