#include <stdio.h>
#include "map.h"
#include "tree.h"
#include "loc.h"
#include "stack.h"
#include "moves.h"
#define NOMINMAX
#include <Windows.h>
#include "graphics.h"

int main()
{
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
    t_tree* tree = create_tree(4, map, start);
    t_node* min_node = getMinRec(tree);
    printf("Cout min : %d\n",min_node->cost);
    printf("cout racine : %d\n",tree->root->cost);
    t_stack minPath = findMinCostPath(tree);
    printf("Nb element chemin %d\n",minPath.nbElts);
    printf("Cout a parcourir pour arriver au noeud minimum: ");
    displayStack2(minPath);
    printf("\n");

    graphic();
    return 0;
}


