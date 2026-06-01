#include "Game.hpp"
#include <raylib.h>

void Game::run()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Geometry Dash");
    SetWindowMinSize(1920, 1080);
    SetTargetFPS(60);
    Texture2D background = LoadTexture("../assets/bg3.png");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        DrawTexture(background, 0, 0, WHITE);
        DrawText("Geometry Dash", 10, 10, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();
}