#include "game.hpp"
#include <raylib.h>

enum class GameState
{
    MENU,
    LEVEL_SELECT
};

struct Level
{
    const char* name;
    Rectangle rect;
};

void Game::run()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(800, 600, "Geometry Dash");
    SetWindowMinSize(800, 600);
    SetWindowMaxSize(1920, 1080);
    SetTargetFPS(60);

    TraceLog(LOG_INFO, GetWorkingDirectory());

    // Assets
    Texture2D background = LoadTexture("../assets/bg3.png");
    Texture2D playButton  = LoadTexture("../assets/playbutton.png");
    Texture2D logo        = LoadTexture("../assets/logo.png");
    Texture2D backButton  = LoadTexture("../assets/backbutton.png");

    GameState state = GameState::MENU;

    // -------------------
    // LEVELS (DATA DRIVEN)
    // -------------------
    Level levels[4] = {
        { "STEREO MADNESS", {0,0,300,80} },
        { "THE NIGHTMARE",  {0,0,300,80} },
        { "EVERY END",      {0,0,300,80} },
        { "ICE CREAM",      {0,0,300,80} }
    };

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();
        bool clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        // -------------------
        // DYNAMIC LAYOUT
        // -------------------
        for (int i = 0; i < 4; i++)
        {
            levels[i].rect.x = (GetScreenWidth() - 300) / 2.0f;
            levels[i].rect.y = 200 + i * 100;
        }

        Rectangle playRect = {
            GetScreenWidth()/2.0f - (playButton.width * 0.25f),
            GetScreenHeight()/2.0f - (playButton.height * 0.25f),
            playButton.width * 0.5f,
            playButton.height * 0.5f
        };

        Rectangle backRect = {
            20,
            20,
            backButton.width * 0.2f,
            backButton.height * 0.2f
        };

        // -------------------
        // INPUT
        // -------------------
        if (state == GameState::MENU && clicked)
        {
            if (CheckCollisionPointRec(mouse, playRect))
                state = GameState::LEVEL_SELECT;
        }

        if (state == GameState::LEVEL_SELECT && clicked)
        {
            if (CheckCollisionPointRec(mouse, backRect))
                state = GameState::MENU;

            for (int i = 0; i < 4; i++)
            {
                if (CheckCollisionPointRec(mouse, levels[i].rect))
                {
                    TraceLog(LOG_INFO, levels[i].name);
                }
            }
        }

        // -------------------
        // DRAW
        // -------------------
        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(
            background,
            {0,0,(float)background.width,(float)background.height},
            {0,0,(float)GetScreenWidth(),(float)GetScreenHeight()},
            {0,0},
            0,
            WHITE
        );

        if (state == GameState::MENU)
        {
            int logoX = (GetScreenWidth() - logo.width) / 2;
            int logoY = (int)(GetScreenHeight() * 0.093f);

            DrawTexture(logo, logoX, logoY, WHITE);

            Rectangle src = {0,0,(float)playButton.width,(float)playButton.height};
            Rectangle dst = {
                GetScreenWidth()/2.0f,
                GetScreenHeight()/2.0f,
                playButton.width * 0.5f,
                playButton.height * 0.5f
            };

            DrawTexturePro(
                playButton,
                src,
                dst,
                {dst.width/2, dst.height/2},
                0,
                WHITE
            );
        }
        else if (state == GameState::LEVEL_SELECT)
        {
            DrawText("LEVEL SELECT",
                GetScreenWidth()/2 - 120,
                100,
                40,
                WHITE
            );

            DrawTexturePro(
                backButton,
                {0,0,(float)backButton.width,(float)backButton.height},
                backRect,
                {0,0},
                0,
                WHITE
            );

            for (int i = 0; i < 4; i++)
            {
                DrawRectangleRec(levels[i].rect, DARKGRAY);
                DrawRectangleLinesEx(levels[i].rect, 3, WHITE);

                DrawText(
                    levels[i].name,
                    levels[i].rect.x + 20,
                    levels[i].rect.y + 25,
                    20,
                    WHITE
                );
            }
        }

        EndDrawing();
    }

    UnloadTexture(background);
    UnloadTexture(playButton);
    UnloadTexture(logo);
    UnloadTexture(backButton);

    CloseWindow();
}