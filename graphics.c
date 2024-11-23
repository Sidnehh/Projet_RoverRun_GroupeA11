//
// Created by Sidney (Ingénieur) on 23/11/2024.
//
#include "map.h"
#include "tree.h"
#include <raylib.h>
#include <stdio.h>

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

int graphic()
{
    t_map map = createMapFromFile("..\\maps\\example1.map");
    const int screenWidth = 650;
    const int screenHeight = 600;
    t_localisation robotpos;
    robotpos.pos.x = 0;
    robotpos.pos.y = 0;
    robotpos.ori = SOUTH;
    int movements = 4;
    int i;
    t_tree* tree = create_tree(movements,map,robotpos);
    t_stack path = findMinCostPath2(tree);

    InitWindow(screenWidth, screenHeight, "Test Raylib");
    SetTargetFPS(1);  // Limiter à 60 images par seconde
    while (!WindowShouldClose()) { // Tant que la fenêtre n'est pas fermée
        BeginDrawing();
        ClearBackground(DARKBLUE);  // Effacer l'écran avec une couleur blanche

        for(i=0;i<map.y_max;i++)
        {
            for(int j=0;j<map.x_max;j++)
            {
                DrawRectangle(robotpos.pos.x, robotpos.pos.y, 40, 40, BLACK);
                DrawRectangle(50+i*100, 10+j*100, 80, 80, GetColorFromPos(j,i,map));
            }
        }
        for(i=0;i<movements;i++)
        {
            updateLocalisation(&robotpos, pop(&path));
        }
        // Fin du dessin
        EndDrawing();
    }
    // Fermer la fenêtre et nettoyer les ressources
    CloseWindow();

    return 0;
}