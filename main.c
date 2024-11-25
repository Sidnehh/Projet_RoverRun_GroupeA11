#include <stdio.h>
#include "map.h"
#include "tree.h"
#include "loc.h"
#include "mark.h"
#include "stack.h"
#include "time.h"
#include "moves.h"
#define NOMINMAX
#include <Windows.h>

int main() {
    SetConsoleOutputCP(65001); // Pour pouvoir mettre des caractères spéciaux

    // Charger la carte
    printf("Chargement de la carte...\n");
    t_map map;

#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif

    // Définir la position de départ

    t_localisation start_loc;
    start_loc.pos.x = 0;
    start_loc.pos.y = 0;
    start_loc.ori = SOUTH;

    MarcFullTravel(start_loc, map);

    /*// Chronométrer la construction de l'arbre
    printf("\nConstruction de l'arbre de mouvements...\n");
    clock_t start_time = clock();
    t_tree* tree = create_tree( 3, map, start_loc); // Exemple avec 3 mouvements
    clock_t end_time = clock();
    printf("Temps pour construire l'arbre : %.4f secondes\n",(double)(end_time - start_time) / CLOCKS_PER_SEC);

    // Afficher l'arbre
    printf("\nStructure de l'arbre de mouvements :\n");
    afficher_arbre(tree->root);

    // Rechercher le nœud de coût minimal
    printf("\nRecherche du nœud avec le coût minimal...\n");
    start_time = clock();
    t_node* min_node = getMinRec(tree);
    end_time = clock();
    printf("Coût minimal trouvé : %d\n", min_node->cost);
    printf("Temps pour rechercher le coût minimal : %.4f secondes\n",
           (double)(end_time - start_time) / CLOCKS_PER_SEC);

    // Calculer le chemin jusqu'au nœud minimal
    printf("\nCalcul du chemin vers le coût minimal...\n");
    start_time = clock();
    t_stack minPath = findMinCostPath(tree);
    end_time = clock();
    printf("Chemin minimal : ");
    displayStack(minPath); // Affiche la pile des mouvements menant au nœud minimal
    printf("\nTemps pour calculer le chemin minimal : %.4f secondes\n",
           (double)(end_time - start_time) / CLOCKS_PER_SEC);

    // Libération de la mémoire
    printf("\n Libération de la mémoire...\n");
    start_time = clock();
    free_tree(tree);
    end_time = clock();
    printf("Temps pour libérer la mémoire : %.4f secondes\n",
           (double)(end_time - start_time) / CLOCKS_PER_SEC);*/


    return 0;
}