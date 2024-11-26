//
// Created by Sidney (Ingénieur) on 25/11/2024.
//

#include "mark.h"
#include <stdio.h>

t_localisation ExecutePhase(t_localisation start_pos, t_map map, int nb_movements)
{
    t_tree* tree = create_tree(nb_movements, map, start_pos);
    t_stack path = findMinCostPath(tree);
    t_move curr_mov;
    printf("Début de la phase ! Il est en %d,%d, orienté %d\n", start_pos.pos.x, start_pos.pos.y, start_pos.ori);
    for(int i = 0; i<nb_movements; i++)
    {
        curr_mov = pop(&path);
        start_pos = predictLocalisation(start_pos, curr_mov);
        printf("Mouvement %d :Marc est actuellement en %d %d, orienté %d, après avoir fait %s\n",
               i+1, start_pos.pos.x, start_pos.pos.y, start_pos.ori, getMoveAsString(curr_mov));
    }
    return start_pos;
}

void MarcFullTravel(t_localisation start_pos, t_map map)
{
    printf("Marc commence son aventure !\n");
    int nb_phases = 0;
    while(map.costs[start_pos.pos.x][start_pos.pos.y] != 0)
    {
        if(map.soils[start_pos.pos.x][start_pos.pos.y] == REG)
        {
            printf("Aïe, un REG martien, prochaine phase, Marc ne peut faire que 4 mouvements...\n");
            start_pos = ExecutePhase(start_pos, map, 4);
        }
        else
        {
            start_pos = ExecutePhase(start_pos, map, 9);
            nb_phases++;
        }
    }
    printf("Marc est arrivé à la base !\n");
}




