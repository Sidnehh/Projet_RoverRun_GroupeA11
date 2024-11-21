//
// Created by Sabrina on 19/11/2024.
//

#include "tree.h"
#include "moves.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "map.h"
#include "stack'.h"
#include "queue'.h"


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


t_tree* allocate_tree(int nb_movements)
{
    // Allocation de la mémoire pour la structure de l'arbre
    t_tree* tree = (t_tree*) malloc(sizeof(t_tree));
    if (tree == NULL) // Vérifie si l'allocation a échoué
    {
        printf("il y a une erreur d'allocation"); // Message d'erreur en cas d'échec
        return NULL; // Retourne NULL pour signaler une erreur
    }

    // Initialisation du nombre de mouvements (capacité maximale des enfants pour la racine)
    tree->nb_movements = nb_movements;

    // Définition des paramètres initiaux pour la racine de l'arbre
    t_localisation initial_loc = loc_init(0, 0, NORTH); // Position initiale de la racine (origine)
    t_move initial_movement = U_TURN;    // Mouvement initial (neutre dans ce cas)
    int initial_cost = 0;                // Coût initial (zéro pour la racine)

    // Création et allocation de la racine de l'arbre
    tree->root = create_node(initial_loc, initial_movement, initial_cost, nb_movements,NULL);
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
    if (nb_children<=0 || nb_children + parent->num_children > parent->max_children)
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
        t_node* child = create_node(new_loc,movement,cost,parent->max_children,parent);

        if (child == NULL) {
            printf("Erreur : Impossible de créer l'enfant %d.\n", i);
            continue; // Passe à l'enfant suivant
        }
        add_child (parent, child);
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


t_node* find_min_cost_node(t_tree* tree) {
    if (tree == NULL || tree->root == NULL) {
        printf("Erreur : L'arbre est vide.\n");
        return NULL;
    }

    t_node* min_node = NULL; // Pointeur vers le nœud de coût minimal
    int min_cost = COST_UNDEF;  // Valeur initiale du coût minimal

    // Création de la file d'exploration
    t_queue exploration = createQueue(100);
    enqueue(&exploration, tree->root); // Commence par la racine

    while (exploration.first != exploration.last) { // Tant que la file n'est pas vide
        t_node* current = dequeue(&exploration); // Récupère un nœud à explorer

        // Si c'est une feuille, compare son coût total
        if (current->num_children == 0 && current->total_cost < min_cost) {
            min_cost = current->total_cost;
            min_node = current; // Met à jour le nœud de coût minimal
        }

        // Enfile tous les enfants du nœud actuel pour exploration
        for (int i = 0; i < current->num_children; i++) {
            enqueue(&exploration, current->children[i]);
        }
    }

    return min_node; // Retourne le nœud avec le coût minimal
}

void find_min_path(t_tree* tree) {
    if (tree == NULL || tree->root == NULL) {
        printf("Erreur : L'arbre est vide.\n");
        return;
    }

    // Trouve la feuille avec le coût total minimal
    t_node* min_node = find_min_cost_node(tree);
    if (min_node == NULL) {
        printf("Erreur : Aucun chemin trouvé.\n");
        return;
    }

    // Pile pour construire le chemin dans l'ordre inverse
    t_stack path_stack = createStack(100);
    t_node* current = min_node;

    // Remonte jusqu'à la racine et empile les nœuds
    while (current != NULL) {
        push(&path_stack, current); // Empile le nœud
        current = current->parent; // Passe au parent
    }

    // Affiche le chemin depuis la racine vers la feuille
    printf("Chemin minimal (racine → feuille) :\n");
    while (path_stack.nbElts > 0) {
        t_node* node = pop(&path_stack);
        printf("Position : (%d, %d), Coût Total : %d\n", node->loc.pos.x, node->loc.pos.y, node->total_cost);
    }
}
