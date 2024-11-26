//
// Created by Sidney (Ingénieur) on 23/11/2024.
//
#include "map.h"
#include "tree.h"
#include <raylib.h>
#include <stdio.h>

int GetOrientationPosX(t_orientation orientation)
{
    switch(orientation)
    {
        case EAST:
            return 1;
        case WEST:
            return -1;
        default:
            return 0;
    }
}
int GetOrientationPosY(t_orientation orientation)
{
    switch(orientation)
    {
        case NORTH:
            return -1;
        case SOUTH:
            return 1;
        default:
            return 0;
    }
}

Color GetColorFromPos(int x, int y, t_map map)
{
    Color color;
    t_soil soil_type = map.soils[x][y];
    switch (soil_type)
    {
        case BASE_STATION:
            color = GRAY;
            break;
        case PLAIN:
            color = GREEN;
            break;
        case ERG:
            color = YELLOW;
            break;
        case REG:
            color = ORANGE;
            break;
        case CREVASSE:
            color = BLACK;
            break;
    }
    return color;
}


int graphic(t_map map, t_localisation pos)
{
    t_stack path = findMinCostPath(create_tree(9,map,pos));
    const int screenWidth = 800;
    const int screenHeight = 800;
    t_localisation robotpos = pos;
    int rectangleposx = 0;
    int rectangleposy = 0;
    int i;
    int phases = 2;
    int custom_height = screenHeight/10;
    int custom_width = screenWidth/10;
    int custom_gap = screenWidth/10;
    printf("Phase 1: \n");


    InitWindow(screenWidth, screenHeight, "");
    SetTargetFPS(1);  // Limiter à 60 images par seconde
    while (!WindowShouldClose()) { // Tant que la fenêtre n'est pas fermée
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for(i=0;i<map.y_max-1;i++)
        {
            for(int j=0;j<map.x_max;j++)
            {
                DrawRectangle(50+i*100, 10+j*100, custom_width, custom_height, GetColorFromPos(j,i,map));
            }
        }
        rectangleposx = robotpos.pos.x*100+70;
        rectangleposy = robotpos.pos.y*100+30;
        DrawRectangle(rectangleposx, rectangleposy, 40, 40, BLACK);
        DrawRectangle(rectangleposx+15+10* GetOrientationPosX(robotpos.ori), rectangleposy+15+10* GetOrientationPosY(robotpos.ori),10,10,BLUE);

        if(path.nbElts>0)
        {
            updateLocalisation(&robotpos, pop(&path));
        }
        else
        {
            if(map.costs[robotpos.pos.x][robotpos.pos.y]!=0)
            {
                printf("Phase: %d\n", phases++);
                path = findMinCostPath(create_tree(9, map, robotpos));
            }
            else
                printf("Trouvé.\n");
        }
        printf("x:%d, y:%d, cost:%d\n", robotpos.pos.x, robotpos.pos.y, map.costs[robotpos.pos.x][robotpos.pos.y]);
        // Fin du dessin
        EndDrawing();
    }
    // Fermer la fenêtre et nettoyer les ressources
    CloseWindow();

    return 0;
}