#include <stdio.h>
#include "map.h"
#include "tree.h"
#include "loc.h"
#include "moves.h"
#define NOMINMAX
#include <Windows.h>

int main() {
    SetConsoleOutputCP(65001); // Pour pouvoir mettre des caractères spéciaux
    t_map map;
    t_localisation start_loc;
    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif
    t_localisation start;
    start.pos.x = 0;
    start.pos.y = 0;
    start.ori = SOUTH;
    t_tree* tree = create_tree(3, map, start);
    afficher_arbre(tree->root);
    t_node* min_node = getMinRec(tree);
    printf("Cout min : %d\n",min_node->cost);
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
    return 0;
}


