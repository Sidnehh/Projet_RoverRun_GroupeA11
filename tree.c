#include "tree.h"
#include "moves.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "queue.h"
#include "map.h"
#include <math.h>
#include "moves.h"
#include "loc.h"
#include <stdbool.h>

bool is_position_visited(t_position pos, t_localisation *visited_positions, int visited_count) {
    for (int i = 0; i < visited_count; i++) {
        // Comparer les coordonnées x et y de la position
        if (visited_positions[i].pos.x == pos.x && visited_positions[i].pos.y == pos.y) {
            return true;  // Position déjà visitée
        }
    }
    return false;  // Position non visitée
}
int factorial(int n) {
    if (n < 0) {
        printf("Erreur : la factorielle n'est pas définie pour les nombres négatifs.\n");
        return -1;
    }
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

t_node* create_node(t_localisation loc, t_move mvt_for_access, int cost) {
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

void display_node(t_node* node)
{
    if (node==NULL){
        printf("Erreur: affichage du noeud impossible");
        return;
    }

    else{
        char * move_string = getMoveAsString(node->mvt_for_access);
        printf("Noeud à la position: (%d, %d)\nMouvement pour y accèder : %s\nCoût:%d\nNombre d'enfant:%d\n",
               node->loc.pos.x,node->loc.pos.y,move_string,node->cost,node->num_children);
        return;
    }
}

void free_node(t_node* node)
{
    if (node == NULL)
    {
        return;
    }
    if(node->num_children > 0 && node->children != NULL)
    {
        for(int i=0; i < node -> num_children; i++){
            free_node(node->children[i]);
        }
    }
    free(node);
}

t_tree* allocate_tree(t_node* racine, int profondeur)
{
    t_tree* tree = (t_tree*)malloc(sizeof(t_tree));
    if (tree == NULL || racine == NULL )
    {
        printf("Erreur: allocation mémoire inaboutie");
        return NULL;
    }
    tree->root = racine;
    tree->profondeur =profondeur;
    return tree;
}

void free_tree(t_tree* tree){
    if(tree == NULL){
        return;
    }
    free_node(tree->root);
    free(tree);
}

void add_child(t_node* parent, t_node* child){
    if(parent == NULL || child == NULL){
        printf("Erreur : L'enfant ou le parent est invalide");
        return;
    }
    t_node ** new_children_list = (t_node**)realloc(parent->children,sizeof(t_node*)*(parent->num_children+1));
    if(new_children_list == NULL){
        printf("Erreur : Ajout du nouvelle enfant impossible");
        return;
    }
    parent->num_children += 1;
    parent->children = new_children_list;
    child->parent = parent;
}

t_node* create_tree(t_node* racine, t_map map, t_move* list_mvt_utilisable, int nb_movement_possible, int nb_movement_max) {
    t_queue queue_node_position = createQueue(100);
    enqueue(&queue_node_position, racine->loc.pos); // Enfile la localisation racine

    while (!is_empty(&queue_node_position)) {
        t_position cur_loc = dequeue(&queue_node_position);

        t_localisation cur_localisation = {cur_loc};
        t_node* cur_node = create_node(cur_localisation, F_10, map.costs[cur_loc.y][cur_loc.x]);

        if (cur_node == NULL) {
            printf("Erreur: impossible de créer un nœud\n");
            continue;
        }

        // Affichage de l'état actuel
        printf("Création d'un nœud à la position: (%d, %d)\n", cur_loc.x, cur_loc.y);

        // Ajout des enfants pour les mouvements valides
        for (int i = 0; i < nb_movement_possible && cur_node->num_children < nb_movement_max; i++) {
            t_move move1 = list_mvt_utilisable[i];
            t_localisation new_loc = move(cur_localisation, move1);

            if (new_loc.pos.x < 0 || new_loc.pos.x >= map.x_max || new_loc.pos.y < 0 || new_loc.pos.y >= map.y_max) {
                continue;
            }

            t_node* child = create_node(new_loc, move1, map.costs[new_loc.pos.y][new_loc.pos.x]);
            if (child != NULL) {
                add_child(cur_node, child);
                enqueue(&queue_node_position, new_loc.pos);
            }

            // Supprimer le mouvement de la liste
            for (int j = i; j < nb_movement_possible - 1; j++) {
                list_mvt_utilisable[j] = list_mvt_utilisable[j + 1];
            }
            nb_movement_possible--;
            i--;
        }
    }

    return racine;
}


void afficher_arbre(t_node* root) {
    if (root == NULL) {
        return;
    }
    printf("Noeud à la position: (%d, %d)\n", root->loc.pos.x, root->loc.pos.y);
    printf("Mouvement pour y accéder : %c %dm\n", root->mvt_for_access, root->cost);
    printf("Coût: %d\n", root->cost);
    printf("Nombre d'enfants: %d\n", root->num_children);

    // Afficher les enfants récursivement
    for (int i = 0; i < root->num_children; i++) {
        afficher_arbre(root->children[i]);
    }
}




