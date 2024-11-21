// Created by SURFACE on 12/11/2024.

#include "loc.h"
#include "moves.h"
#include "map.h"
#include "queue.h"
#include <stdbool.h>
#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

// Structures requises à l'utilisation des arbres

// Définition d'un nœud dans l'arbre, représentant un mouvement spécifique
typedef struct s_node
{
    struct s_node ** children;    // Pointeur vers le tableau des enfants du nœud
    struct s_node * parent;       // Pointeur vers le parent, pour retracer le chemin

    t_localisation loc;// Position du noeud sur la grille
    t_move mvt_for_access;              // Mouvement effectué pour atteindre cette position

    int cost;                     // Coût associé pour atteindre cette position
    int num_children;             // Nombre d'enfants actuels (utile pour les parcours)
} t_node;

// Fonction factorial
int factorial(int n);
bool is_position_visited(t_position pos, t_localisation *visited_positions, int visited_count);
// Initialise un nœud avec une position, un mouvement et un coût
t_node* create_node(t_localisation loc, t_move mvt_for_access, int cost);

// Affichage du noeud
void display_node(t_node* node);

// Libère la mémoire allouée pour un nœud et ses enfants
void free_node(t_node* node);

// Définition de la structure de l'arbre lui-même
typedef struct s_tree
{
    t_node* root;   // Pointeur vers la racine de l'arbre
    int profondeur; //Profondeur de l'arbre
} t_tree;
void resize_queue(t_queue *queue);
// Fonctions de gestion de l'arbre (prototypes)

//Création d'un arbre on lui alloue une racine et une profondeur
t_tree* allocate_tree(t_node* racine, int profondeur);

//Libère la mémoire allouée pour un arbre
void free_tree(t_tree* tree);

// Ajoute un enfant à un nœud parent
void add_child(t_node* parent, t_node* child);

t_node* create_tree(t_node* racine, t_map map, t_move* list_mvt_utilisable, int nb_movement_possible, int nb_movement_max);
void afficher_arbre(t_node* root) ;

//t_node* find_min_node(t_node* root);
//int compare_positions(t_position pos1, t_position pos2);
// Recherche le chemin depuis la racine vers la feuille de valeur minimale d'un arbre
//t_position* find_min_path(t_node* root, t_node* target, int* path_length);


#endif // UNTITLED1_TREE_H