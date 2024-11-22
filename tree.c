//
// Created by Sabrina on 19/11/2024.
//

#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
    new_node->children = (t_node**) malloc(nb_children*sizeof(t_node*));
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

    // Création et allocation de la racine de l'arbre
    tree->root = create_node(F_10,0,nb_movements);
    if (tree->root == NULL) {
        printf("Erreur : Impossible d'initialiser la racine.\n");
        free(tree);
        return NULL;
    }
    if (tree->root->children == NULL)
    {
        printf("Erreur d'allocation \n");
        free(tree->root);
        free(tree);
        return NULL;
    }
    // Définition des paramètres initiaux pour la racine de l'arbre
    tree->root->mvt_for_access = U_TURN;                        // Mouvement initial (neutre dans ce cas)
    tree->root->cost = 0;                                       // Coût initial (zéro pour la racine)
    tree->root->num_children = 0;


    // Retourne le pointeur vers l'arbre initialisé
    return tree;
}

void add_child(t_node* parent, t_node* child)
{
    if(parent == NULL || child == NULL)
    {
        printf("Erreur : L'enfant ou le parent est invalide");
        return;
    }
    parent->children[parent->num_children] = child;
    parent->num_children++;
    child->parent = parent;
}

//Crée une structure de n enfants à un noeud
void build_from_node(t_node* parent, int nb_children, t_localisation curr_loc, t_map map)
{
    if (parent==NULL || nb_children <= 0)
    {
        return;
    }
    t_node *temp_node;
    for(int i=0;i<nb_children;i++)
    {
        temp_node = create_node(*getRandomMoves(nb_children),map.costs[curr_loc.pos.x][curr_loc.pos.y], nb_children-1);
        add_child(parent, temp_node);
        updateLocalisation(&curr_loc, temp_node->mvt_for_access);
        build_from_node(temp_node, nb_children-1, curr_loc,map);
    }
}

// Crée un arbre retraçant les mouvements et coûts possibles par rapport à une carte et la position du Rover
t_tree* create_tree(int nb_movements, t_map map, t_localisation start_loc)
{
    t_tree *p_tree = allocate_tree(nb_movements);
    if (p_tree == NULL) {
        printf("Erreur : Impossible d'allouer l'arbre.\n");
        return NULL;
    }
    build_from_node(p_tree->root,nb_movements,start_loc,map);
    return p_tree;
}

void afficher_arbre(t_node* root)
{
    if (root == NULL)
    {
        return;
    }
    // Afficher les enfants récursivement
    for (int i = 0; i < root->num_children; i++)
    {
        printf("\n");
        printf("Mouvement pour y acceder : %c %dm\n", root->mvt_for_access, root->cost);
        printf("Cout: %d\n", root->cost);
        printf("Nombre d'enfants: %d\n", root->num_children);
        printf("\n");
        afficher_arbre(root->children[i]);
    }
}

t_node* find_min_cost_node(t_tree* tree);

void find_min_path(t_tree* tree);