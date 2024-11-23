//
// Created by Sabrina on 19/11/2024.
//

#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


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
    if (parent==NULL)
    {
        return;
    }
    t_node *temp_node;
    t_move new_mov;
    t_localisation new_pos;
    t_move* moves = getRandomMoves(nb_children);
    for(int i=0;i<nb_children;i++)
    {
        new_mov = moves[i];
        new_pos = predictLocalisation(curr_loc, new_mov);
        if(checkValidPosition(new_pos.pos,map)==0)
        {
            printf("Le robot est mort. \n");
            return;
        }
        temp_node = create_node(new_mov, map.costs[new_pos.pos.x][new_pos.pos.y], nb_children - 1);
        add_child(parent, temp_node);
        build_from_node(temp_node, nb_children - 1, new_pos, map);
    }
}

// Crée un arbre retraçant les mouvements et coûts possibles par rapport à une carte et la position du Rover
t_tree* create_tree(int nb_movements, t_map map, t_localisation start_loc)
{
    t_tree *p_tree = allocate_tree(nb_movements);
    p_tree->root->cost = map.costs[start_loc.pos.x][start_loc.pos.y];
    build_from_node(p_tree->root,nb_movements,start_loc,map);
    return p_tree;
}

void afficher_arbre(t_node* root)
{
    if (root == NULL)
    {
        return;
    }
    printf("\n");
    printf("Mouvement pour y acceder : %s\n", getMoveAsString(root->mvt_for_access));
    printf("Cout: %d\n", root->cost);
    printf("Nombre d'enfants: %d\n", root->num_children);
    printf("\n");
    for (int i = 0; i < root->num_children; i++)
    {
        afficher_arbre(root->children[i]);
    }
}

t_node* find_min_cost_node(t_node* cur_node, t_node* min_node){
    if(cur_node== NULL){
        printf("Erreur: arbre vide");
    }
    if(cur_node->cost < min_node->cost){
        min_node = cur_node;
    }
    for (int i = 0; i < cur_node->num_children; i++) {
        min_node = find_min_cost_node(cur_node->children[i], min_node);
    }
    return min_node;
}

t_node* getMinRec(t_tree* tree){
    if(tree == NULL || tree -> root == NULL)
    {
        return NULL;
    }
    t_node* i_node = (t_node*)malloc(sizeof(t_node));
    if(i_node == NULL){
        printf("Erreur");
    }
    i_node->cost = 15000;// On crée un noeud avec un coût très élevé
    t_node * result = find_min_cost_node(tree->root,i_node);
    return result;
}

t_stack findMinCostPath2(t_tree* tree) {
    if (tree == NULL || tree->root == NULL) {
        printf("Erreur : arbre ou racine vide.\n");
        return createStack(0);
    }

    // Trouver le nœud de coût minimal
    t_node* min_node = getMinRec(tree);
    if (min_node == NULL) {
        printf("Erreur : nœud minimal introuvable.\n");
        return createStack(0); // Retourne une pile vide
    }

    // Initialisation de la pile pour le chemin minimal
    t_node *cur_node = min_node;
    t_stack stackMinPath = createStack(tree->root->mvt_for_access);

    while (cur_node != tree->root) {
        push(&stackMinPath, cur_node->mvt_for_access);
        cur_node = cur_node->parent;
    }

    push(&stackMinPath, tree->root->mvt_for_access);

    t_stack stackMinPathOrder = createStack(stackMinPath.nbElts);

    while (!isEmptyStack(stackMinPath)) {
        push(&stackMinPathOrder, pop(&stackMinPath));
    }

    return stackMinPathOrder; // Retourne la pile contenant le chemin minimal inversé
}

t_stack findMinCostPath(t_tree* tree) {
    if (tree == NULL || tree->root == NULL) {
        printf("Erreur : arbre ou racine vide.\n");
        return createStack(0);
    }

    // Trouver le nœud de coût minimal
    t_node* min_node = getMinRec(tree);
    if (min_node == NULL) {
        printf("Erreur : nœud minimal introuvable.\n");
        return createStack(0); // Retourne une pile vide
    }

    // Initialisation de la pile pour le chemin minimal
    t_node *cur_node = min_node;
    t_stack stackMinPath = createStack(tree->root->num_children);

    while (cur_node != tree->root) {
        push(&stackMinPath, cur_node->cost);
        cur_node = cur_node->parent;
    }

    push(&stackMinPath, tree->root->cost);

    t_stack stackMinPathOrder = createStack(stackMinPath.nbElts);

    while (!isEmptyStack(stackMinPath)) {
        push(&stackMinPathOrder, pop(&stackMinPath));
    }

    return stackMinPathOrder; // Retourne la pile contenant le chemin minimal inversé
}






