//
// Created by SURFACE on 20/11/2024.
//
#include "tree.h"
#include "moves.h"
#include "map.h"
#include "stack.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Initialisation de la carte
    printf("Création d'une carte d'entraînement...\n");
    t_map map = createTrainingMap(); // Crée une carte d'entraînement par défaut
    displayMap(map); // Affiche la carte pour vérifier

    // Nombre de mouvements à explorer
    int nb_movements = 5;

    // Création de l'arbre
    printf("\nCréation de l'arbre avec %d mouvements...\n", nb_movements);
    t_tree* tree = create_tree(nb_movements, map);
    if (tree == NULL) {
        printf("Erreur : Impossible de créer l'arbre.\n");
        return EXIT_FAILURE;
    }

    // Recherche du nœud de coût minimal
    printf("\nRecherche de la feuille avec le coût total minimal...\n");
    t_node* min_node = find_min_cost_node(tree);
    if (min_node == NULL) {
        printf("Erreur : Aucun nœud minimal trouvé.\n");
        free(tree);
        return EXIT_FAILURE;
    }

    // Affiche les informations du nœud minimal
    printf("Nœud de coût minimal trouvé :\n");
    printf("Position : (%d, %d)\n", min_node->loc.pos.x, min_node->loc.pos.y);
    printf("Orientation : %d\n", min_node->loc.ori);
    printf("Coût Total : %d\n", min_node->total_cost);

    // Recherche et affichage du chemin minimal
    printf("\nAffichage du chemin minimal :\n");
    find_min_path(tree);

    // Libération de la mémoire
    printf("\nLibération de la mémoire...\n");
    free_node(tree->root);
    free(tree);

    return EXIT_SUCCESS;
}
