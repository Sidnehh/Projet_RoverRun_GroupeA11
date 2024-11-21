#include <stdio.h>
#include "map.h"
#include "tree.h"
#include "loc.h"


int main() {
    t_map map;
    t_localisation start_loc;
    start_loc.pos.x = 0;
    start_loc.pos.y = 0;
    start_loc.ori = SOUTH;
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
    t_tree* tree = create_tree(4, map, start);
    afficher_arbre(tree->root);
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


