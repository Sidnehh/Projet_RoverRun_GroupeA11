//
// Created by gabby on 21/11/2024.
//
#include "node.h"
#include <stdio.h>
#include <stdlib.h>

// Initialise un nœud avec une position, un mouvement et un coût
t_node* create_node(t_localisation loc, t_move mov, int cost, int max_children,t_node* parent)
{
    t_node *node = (t_node *) malloc(sizeof(t_node)); // Allocation de mémoire
    if (node == NULL) //Vérification de l'allocation de mémoire
    {
        printf("Erreur d'allocation : Le noeud n'a pas pu être créé. \n");
        return NULL;
    }
    node->children = (t_node**) malloc(max_children * sizeof(t_node*)); //Initialisation du tableau de noeuds enfants
    if (node->children == NULL) //Vérification de l'allocation de mémoire
    {
        printf("Erreur d'allocation : Les noeuds enfant n'ont pas pu être créés.");
        return NULL;
    }
    node->num_children = 0;
    node->max_children = max_children;
    node->loc =loc;
    node->cost = cost; // Initialisation de l'attribut coût
    node->movement = mov; // Initialisation de l'attribut mouvement
    node->parent = parent;

    if (parent != NULL) {
        node->total_cost = cost + parent->total_cost;
    } else {
        node->total_cost = cost; // Si pas de parent (racine), le coût total est égal au coût du nœud
    }


    for (int i = 0; i < max_children; i++)
        node->children[i] = NULL;

    return node;
}

// Libère la mémoire allouée pour un nœud et récursivement pour tous ses enfants
void free_node(t_node* node)
{
    // Vérifie si le nœud est NULL avant de tenter de le libérer
    if (node == NULL)
        return; // Si le nœud est NULL, il n'y a rien à libérer, donc on quitte la fonction

    // Parcours récursif de tous les enfants du nœud
    for (int i = 0; i < node->num_children; i++)
    {
        // Libère la mémoire allouée pour chaque enfant
        free_node(node->children[i]);
    }

    // Libère la mémoire allouée pour le tableau de pointeurs `children`
    free(node->children);

    // Libère la mémoire allouée pour le nœud lui-même
    free(node);
}


// Ajoute un enfant au tableau des enfants d'un nœud parent
void add_child(t_node* parent, t_node* child)
{
    // Vérifie si le tableau d'enfants du parent est déjà plein
    if (parent->num_children >= parent->max_children)
    {
        printf("Erreur : Nombre maximum d'enfants atteint pour ce nœud.\n");
        return; // Quitte la fonction sans ajouter l'enfant
    }

    // Ajoute l'enfant au tableau à l'indice donné par num_children
    parent->children[parent->num_children] = child;

    // Met à jour le pointeur parent de l'enfant pour qu'il pointe vers le nœud parent
    child->parent = parent;

    // Incrémente le compteur d'enfants pour indiquer qu'un nouvel enfant a été ajouté
    parent->num_children++;
}