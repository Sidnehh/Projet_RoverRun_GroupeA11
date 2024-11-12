// Created by SURFACE on 12/11/2024.

#include "loc.h"
#include "moves.h"

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

// Définition d'un nœud dans l'arbre, représentant un mouvement spécifique
typedef struct s_node
{
    struct s_node ** children;    // Pointeur vers les enfants du nœud
    struct s_node * parent;       // Pointeur vers le parent, pour retracer le chemin
    t_position localisation;      // Position de MARC après ce mouvement
    t_move movement;              // Mouvement effectué pour atteindre cette position
    int cost;                     // Coût associé pour atteindre cette position
    int num_children;             // Nombre d'enfants actuels (utile pour les parcours)
} t_node;

// Définition de la racine de l'arbre, qui ne représente pas un mouvement, mais sert de point de départ
typedef struct s_root
{
    int cost;                    // Coût de départ initialisé, généralement zéro
    struct s_node ** children;   // Enfants directs représentant les premiers choix de mouvements
} t_root;

// Définition de la structure de l'arbre lui-même
typedef struct s_tree
{
    t_root* tree;   // Pointeur vers la racine de l'arbre
} t_tree;

// Fonctions de gestion de l'arbre (prototypes)
// Initialise un nœud avec une position, un mouvement et un coût
t_node* create_node(t_position pos, t_move mov, int cost);

// Libère la mémoire allouée pour un nœud et ses enfants
void free_node(t_node* node);

// Ajoute un enfant à un nœud parent
void add_child(t_node* parent, t_node* child);gi

#endif // UNTITLED1_TREE_H
