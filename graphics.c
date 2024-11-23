//
// Created by Sidney (Ingénieur) on 23/11/2024.
//
#include "raylib.h"
#include "graphics.h"
int graphic()
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Test Raylib");

    // Définir la couleur du fond de la fenêtre
    SetTargetFPS(60);  // Limiter à 60 images par seconde

    while (!WindowShouldClose()) { // Tant que la fenêtre n'est pas fermée
        // Commencer à dessiner
        BeginDrawing();
        ClearBackground(RAYWHITE);  // Effacer l'écran avec une couleur blanche

        // Dessiner un cercle au centre de la fenêtre
        DrawCircle(screenWidth / 2, screenHeight / 2, 50, BLUE);

        // Fin du dessin
        EndDrawing();
    }
    // Fermer la fenêtre et nettoyer les ressources
    CloseWindow();

    return 0;
}