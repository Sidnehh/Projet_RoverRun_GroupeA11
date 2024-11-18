// Created by SURFACE on 12/11/2024.

#include "loc.h"
#include "moves.h"
#include "map.h"

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

// Structures requises à l'utilisation des arbres

// Définition d'un nœud dans l'arbre, représentant un mouvement spécifique
typedef struct s_node
{
    struct s_node ** children;    // Pointeur vers les enfants du nœud
    struct s_node * parent;       // Pointeur vers le parent, pour retracer le chemin
    t_position position;          // Position de MARC après ce mouvement
    t_move movement;              // Mouvement effectué pour atteindre cette position
    int cost;                     // Coût associé pour atteindre cette position
    int num_children;             // Nombre d'enfants actuels (utile pour les parcours)
} t_node;


// Définition de la structure de l'arbre 
typedef struct s_tree
{
    t_node* root;   // Pointeur vers la racine de l'arbre
} t_tree;


// Fonctions de gestion de l'arbre (prototypes)


// Initialise un nœud avec une position, un mouvement et un coût
t_node* create_node(t_position pos, t_move mov, int cost, int nb_children);

// Libère la mémoire allouée pour un nœud et ses enfants
void free_node(t_node* node);

// Ajoute un enfant à un nœud parent
void add_child(t_node* parent, t_node* child);

//Alloue la mémoire d'un arbre selon nombre de mouvements requis
t_tree* allocate_tree(int nb_movements);

//Crée une structure de n enfants à un noeud
void build_from_node(t_node* node, int nb_children, t_localisation position, t_map map);

// Crée un arbre
t_tree* create_tree(int, t_map, t_localisation);

// Recherche la feuille de valeur minimale d'un arbre
t_node find_min_node(t_tree);

// Recherche le chemin depuis la racine vers la feuille de valeur minimale d'un arbre
t_node* find_min_path(t_tree,t_node);


#endif // UNTITLED1_TREE_H
