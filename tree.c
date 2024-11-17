//
// Created by Sidney (Ingénieur) on 12/11/2024.
//

#include "tree.h"
#include "moves.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Initialise un nœud avec une position, un mouvement et un coût
t_node* create_node(t_position pos, t_move mov, int cost, int nb_children)
{
    t_node *node = (t_node *) malloc(sizeof(t_node)); // Allocation de mémoire
    if (node == NULL) //Vérification de l'allocation de mémoire
    {
        printf("Erreur d'allocation : Le noeud n'a pas pu être créé. \n");
        return NULL;
    }
    node->num_children = 0; //Initialisation du nombre de noeuds enfants
    node->children = (t_node**) malloc(nb_children*sizeof(t_node)); //Initialisation du tableau de noeuds enfants
    if (node->children == NULL) //Vérification de l'allocation de mémoire
    {
        printf("Erreur d'allocation : Les noeuds enfant n'ont pas pu être créés.");
        return NULL;
    }
    node->cost = cost; // Initialisation de l'attribut coût
    node->movement = mov; // Initialisation de l'attribut mouvement
    node->position = pos; // Initialisation de l'attribut position
    return node;
}

// Libère la mémoire allouée pour un nœud et ses enfants
void free_node(t_node* node)
{
    if (node==NULL)
        return;

    int nb_enfants = node->num_children;
    int i;
    for(i=0;i<nb_enfants;i++)
    {
        free_node(node->children[i]);
    }
    free(node->children);
    free(node);
}

//Alloue la mémoire d'un arbre selon nombre de mouvements requis
t_tree* allocate_tree(int nb_movements)
{
    t_tree* tree = (t_tree*) malloc(sizeof(t_tree));                                      //Allocation de la mémoire pour l'arbre
    if (tree == NULL)
    {
        printf("Erreur d'allocation : La mémoire pour l'arbre n'a pas été allouée.");
        return NULL;
    }
    tree->root = (t_root *) malloc(sizeof(t_root));                                       //Allocation de la mémoire pour la racine
    if (tree->root == NULL)
    {
        printf("Erreur d'allocation : La mémoire pour la racine n'a pas été allouée.");
        free(tree);
        return NULL;
    }
    tree->root->children = (t_node**) malloc(nb_movements*sizeof(t_node));                //Allocation de mémoire pour les noeuds enfants
    if (tree->root->children == NULL)
    {
        printf("Erreur d'allocation : la mémoire pour noeuds enfants n'a pas été allouée.");
        free(tree->root);
        free(tree);
        return NULL;
    }
    return tree;
}

// Ajoute un enfant à un nœud parent
void add_child(t_node* parent, t_node* child)
{
    parent->children[parent->num_children] = child;
    parent->num_children++;
}

//Crée une structure de n enfants à un noeud
void build_from_node(t_node* root, int nb_movements, t_localisation position, t_map map)
{
    if(root==NULL || nb_movements<=0)
        return;

    t_node* node_temp;                                                                         //Initialisation du noeud temporaire pour créer enfants
    t_position node_pos;                                                                       //Initialisation de variable temporaire t_position
    t_move movement;                                                                           //Initialisation de variable temporaire t_movement
    int cost;                                                                                  //Initialisation d'une variable temporaire cost
    for(int i=0; i<nb_movements; i++)
    {
        movement = (t_move)rand()%7;                                                           //Choix d'un mouvement au hasard parmi les 7 disponibles
        node_pos = translate(position,movement).pos;                                           //Définition de la position du noeud
        cost = map.costs[node_pos.x][node_pos.y];                                              //Définition du coût
        node_temp = create_node(node_pos, movement, cost, nb_movements-1); //Création du noeud
        add_child(root, node_temp);
        build_from_node(node_temp, node_temp->num_children, move(position, node_temp->movement), map);
    }
}

// Crée un arbre retraçant les mouvements et coûts possibles par rapport à une carte et la position du Rover
t_tree* create_tree(int nb_movements, t_map map, t_localisation position)
{
    t_tree* tree = allocate_tree(nb_movements);
    tree->root->cost = 0;                                                                      //Initialisation du coût du noeud racine
    tree->root->num_children = 0;                                                              //Initialisation du nombre de noeuds enfants

    t_node* node_temp;                                                                         //Initialisation du noeud temporaire pour créer enfants
    t_position node_pos;                                                                       //Initialisation de variable temporaire t_position
    t_move movement;                                                                           //Initialisation de variable temporaire t_movement
    int cost;                                                                                  //Initialisation d'une variable temporaire cost
    srand(time(NULL));                                                              //Initialisation du générateur de nombre aléatoire

    build_from_node(tree->root, nb_movements, position, map);
    return tree;
}

// Recherche la feuille de valeur minimale d'un arbre
t_node find_min_node(t_tree tree);
//à compléter

// Recherche le chemin depuis la racine vers la feuille de valeur minimale d'un arbre
t_node* find_min_path(t_tree,t_node);
//à compléter
