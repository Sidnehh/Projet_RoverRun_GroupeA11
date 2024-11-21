#include <stdio.h>
#include "map.h"
#define NOMINMAX
#include <Windows.h>
#include "tree.h"

int main() {
    t_map map;
    SetConsoleOutputCP(65001); // Pour pouvoir mettre des caractères spéciaux
    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);

    // Définition de la position initiale
    t_localisation start_loc = {0, 0};  // Par exemple, la position (0, 0) pour démarrer
    printf("Position départ %d %d\n",start_loc.pos.x,start_loc.pos.y);

    //Nombre de mouvement parmis combien par phase
    t_move list_mvt_utilisable[] = {F_10, F_20, F_30, B_10, T_LEFT, T_RIGHT, U_TURN};  // Mouvement possible (modifier si nécessaire)
    int nb_movement_possible = 7; //Nb d'élément de la liste des utilisable
    int nb_movement_max = 4; // Nombre maximal de mouvements possibles (par exemple, 4 directions)

    // Créer la racine de l'arbre avec la localisation de départ
    t_node* racine = create_node(start_loc, F_10, map.costs[start_loc.pos.y][start_loc.pos.x]);
    printf("Affichage de la racine\n");
    display_node(racine);


    if (racine == NULL) {
        printf("Erreur : impossible de créer la racine de l'arbre.\n");
        return 1;
    }

    // Créer l'arbre à partir de la racine, de la carte et des mouvements possibles
    t_tree* tree = allocate_tree(racine, 3); // Par exemple, profondeur 3
    if (tree == NULL) {
        printf("Erreur : impossible d'allouer la mémoire pour l'arbre.\n");
        return 1;
    }

    // Construire l'arbre avec la fonction create_tree
    create_tree(racine, map, list_mvt_utilisable, nb_movement_possible, nb_movement_max);

    // Afficher l'arbre construit
    printf("\nAffichage de l'arbre construit :\n");
    afficher_arbre(tree->root);

    // Libérer la mémoire allouée pour l'arbre
    free_tree(tree);

    return 0;
}
