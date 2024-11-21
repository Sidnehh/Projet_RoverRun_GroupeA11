//
// Created by Sabrina on 19/11/2024.
//

#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

t_node* create_node(t_localisation loc, t_move mvt_for_access, int cost)
{
    t_node* new_node = (t_node*)malloc(sizeof(t_node));
    if (new_node == NULL) {
        printf("Erreur d'allocation mémoire pour un nœud\n");
        return NULL;
    }

    // Initialisation des valeurs du nœud
    new_node->loc = loc;
    new_node->mvt_for_access = mvt_for_access;
    new_node->cost = cost;
    new_node->num_children = 0;
    new_node->children = NULL;  // Initialisation à NULL, allocation dynamique plus tard
    return new_node;
}



t_tree* allocate_tree(int nb_movements)
{
    // Allocation de la mémoire pour la structure de l'arbre
    t_tree* tree = (t_tree*) malloc(sizeof(t_tree));
    if (tree == NULL) // Vérifie si l'allocation a échoué
    {
        printf("il y a une erreur d'allocation"); // Message d'erreur en cas d'échec
        return NULL;                                     // Retourne NULL pour signaler une erreur
    }

    // Initialisation du nombre de mouvements (capacité maximale des enfants pour la racine)
    tree->nb_movements = nb_movements;

    // Définition des paramètres initiaux pour la racine de l'arbre
    t_localisation initial_loc = loc_init(0, 0, NORTH); // Position initiale de la racine (origine)
    t_move initial_movement = U_TURN;                   // Mouvement initial (neutre dans ce cas)
    int initial_cost = 0;                               // Coût initial (zéro pour la racine)

    // Création et allocation de la racine de l'arbre
    tree->root = create_node(initial_loc, initial_movement, initial_cost);
    if (tree->root == NULL) {
        printf("Erreur : Impossible d'initialiser la racine.\n");
        free(tree);
        return NULL;
    }
    // Retourne le pointeur vers l'arbre initialisé
    return tree;
}



//Crée une structure de n enfants à un noeud
void build_from_node(t_node* parent, int nb_children, t_map map)
{

    if (parent==NULL)
    {
        printf("Le parent est non-existant\n");
        return;
    }
    if (nb_children<=0 || nb_children + parent->num_children > parent->num_children)
    {
        printf("Le nombre d'enfants n'est pas valide\n");
        return;
    }
    for (int i =0; i<nb_children;i++)
    {

        t_move movement = (t_move)(rand() % 7);
        t_localisation new_loc = translate(parent->loc, movement);

        if (!isValidLocalisation(new_loc.pos, map.x_max, map.y_max)) {
            printf("Erreur : Position en dehors des limites pour l'enfant %d.\n", i);
            return;
        }

        int cost = map.costs[new_loc.pos.x][new_loc.pos.y];
        t_node* child = create_node(new_loc,movement,cost);

        if (child == NULL) {
            printf("Erreur : Impossible de créer l'enfant %d.\n", i);
            continue; // Passe à l'enfant suivant
        }
        add_child(parent, child);
        build_from_node(child, nb_children - 1, map);
    }
}

// Crée un arbre retraçant les mouvements et coûts possibles par rapport à une carte et la position du Rover
t_tree* create_tree(int nb_movements, t_map map) {
    t_tree *p_tree = allocate_tree(nb_movements);
    if (p_tree == NULL) {
        printf("Erreur : Impossible d'allouer l'arbre.\n");
        return NULL;
    }
    srand(time(NULL));
    build_from_node(p_tree->root, nb_movements, map);
    return p_tree;
}

t_node* find_min_cost_node(t_tree* tree);

void find_min_path(t_tree* tree);