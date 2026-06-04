#include "hub.hpp"

#include "../pong/game.hpp"
#include "../gd/game.hpp"

#include <raylib.h>

void Hub::run()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Game Hub");
    SetWindowMinSize(800, 600);
    SetWindowMaxSize(1920, 1080);
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();

        Vector2 mouse = GetMousePosition();

        Rectangle pongButton =
        {
            screenWidth / 2.0f - 150.0f,
            screenHeight * 0.35f,
            300.0f,
            80.0f
        };

        Rectangle gdButton =
        {
            screenWidth / 2.0f - 150.0f,
            screenHeight * 0.55f,
            300.0f,
            80.0f
        };

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (CheckCollisionPointRec(mouse, pongButton))
            {
                CloseWindow();

                PongGame pong;
                pong.run();

                InitWindow(800, 600, "Game Hub");
            }

            if (CheckCollisionPointRec(mouse, gdButton))
            {
                CloseWindow();

                GdGame gd;
                gd.run();

                InitWindow(800, 600, "Game Hub");
            }
        }

        BeginDrawing();

        ClearBackground(BLACK);

        const char* title = "GAME HUB";
        int titleSize = 40;

        DrawText(
            title,
            screenWidth / 2 - MeasureText(title, titleSize) / 2,
            screenHeight * 0.13f,
            titleSize,
            WHITE
        );

        DrawRectangleRec(pongButton, DARKBLUE);

        DrawText(
            "PONG",
            pongButton.x + pongButton.width / 2 - MeasureText("PONG", 30) / 2,
            pongButton.y + pongButton.height / 2 - 15,
            30,
            WHITE
        );

        DrawRectangleRec(gdButton, DARKGREEN);

        DrawText(
            "GEOMETRY DASH",
            gdButton.x + gdButton.width / 2 - MeasureText("GEOMETRY DASH", 30) / 2,
            gdButton.y + gdButton.height / 2 - 15,
            30,
            WHITE
        );

        EndDrawing();
    }

    CloseWindow();
}