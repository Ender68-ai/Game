#include "game.hpp"
#include <raylib.h>

enum class GameState
{
    MENU,
    LEVEL_SELECT,
    PLAYING
};

struct Level
{
    const char* name;
    Rectangle rect;
};

void GdGame::run()
{
    InitWindow(1920, 1080, "Geometry Dash");
    SetTargetFPS(60);

    Texture2D background = LoadTexture("../assets/bg3.png");
    Texture2D playButton = LoadTexture("../assets/playbutton.png");
    Texture2D logo = LoadTexture("../assets/logo.png");
    Texture2D backButton = LoadTexture("../assets/backbutton.png");
    Texture2D cube = LoadTexture("../assets/cube.png");

    GameState state = GameState::MENU;
    int currentLevel = -1;

    Level levels[] =
    {
        {"STEREO MADNESS", {0, 0, 300, 80}},
        {"THE NIGHTMARE",  {0, 0, 300, 80}},
        {"EVERY END",      {0, 0, 300, 80}},
        {"ICE CREAM",      {0, 0, 300, 80}}
    };

    constexpr int levelCount = sizeof(levels) / sizeof(levels[0]);

    const float groundY = 1000.0f;

    Rectangle player =
    {
        500.0f,
        groundY - 100.0f,
        100.0f,
        100.0f
    };

    float velocityY = 0.0f;
    bool onGround = true;

    float levelOffset = 0.0f;
    const float scrollSpeed = 5.0f;

    Rectangle spikes[] =
    {
        {800, groundY - 100, 100, 100},
        {920, groundY - 100, 100, 100},
        {1040, groundY - 100, 100, 100}
    };

    constexpr int spikeCount = sizeof(spikes) / sizeof(spikes[0]);

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();
        bool clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        for (int i = 0; i < levelCount; i++)
        {
            levels[i].rect.x = (GetScreenWidth() - levels[i].rect.width) / 2.0f;
            levels[i].rect.y = 200 + i * 100;
        }

        Rectangle playRect =
        {
            GetScreenWidth() / 2.0f - (playButton.width * 0.25f),
            GetScreenHeight() / 2.0f - (playButton.height * 0.25f),
            playButton.width * 0.5f,
            playButton.height * 0.5f
        };

        Rectangle backRect =
        {
            20,
            20,
            backButton.width * 0.2f,
            backButton.height * 0.2f
        };

        if (state == GameState::MENU && clicked)
        {
            if (CheckCollisionPointRec(mouse, playRect))
            {
                state = GameState::LEVEL_SELECT;
            }
        }

        if (state == GameState::LEVEL_SELECT && clicked)
        {
            if (CheckCollisionPointRec(mouse, backRect))
            {
                state = GameState::MENU;
            }

            for (int i = 0; i < levelCount; i++)
            {
                if (CheckCollisionPointRec(mouse, levels[i].rect))
                {
                    currentLevel = i;

                    player.x = 150.0f;
                    player.y = groundY - player.height;

                    velocityY = 0.0f;
                    onGround = true;
                    levelOffset = 0.0f;

                    state = GameState::PLAYING;
                }
            }
        }

        if (state == GameState::PLAYING)
        {
            if (clicked && CheckCollisionPointRec(mouse, backRect))
            {
                state = GameState::LEVEL_SELECT;
            }

            if (currentLevel == 0)
            {
                if ((IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && onGround)
                {
                    velocityY = -30.0f;
                    onGround = false;
                }

                velocityY += 1.4f;
                player.y += velocityY;

                if (player.y >= groundY - player.height)
                {
                    player.y = groundY - player.height;
                    velocityY = 0.0f;
                    onGround = true;
                }

                levelOffset += scrollSpeed;

                for (int i = 0; i < spikeCount; i++)
                {
                    Rectangle spikeRect =
                    {
                        spikes[i].x - levelOffset,
                        spikes[i].y,
                        spikes[i].width,
                        spikes[i].height
                    };

                    if (CheckCollisionRecs(player, spikeRect))
                    {
                        player.y = groundY - player.height;
                        velocityY = 0.0f;
                        onGround = true;
                        levelOffset = 0.0f;
                    }
                }
            }
        }

        BeginDrawing();

        ClearBackground(BLACK);

        DrawTexturePro(
            background,
            {0, 0, (float)background.width, (float)background.height},
            {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
            {0, 0},
            0,
            WHITE
        );

        if (state == GameState::MENU)
        {
            int logoX = (GetScreenWidth() - logo.width) / 2;
            int logoY = (int)(GetScreenHeight() * 0.093f);

            DrawTexture(logo, logoX, logoY, WHITE);

            DrawTexturePro(
                playButton,
                {0, 0, (float)playButton.width, (float)playButton.height},
                {
                    GetScreenWidth() / 2.0f,
                    GetScreenHeight() / 2.0f,
                    playButton.width * 0.5f,
                    playButton.height * 0.5f
                },
                {
                    playButton.width * 0.25f,
                    playButton.height * 0.25f
                },
                0,
                WHITE
            );
        }
        else if (state == GameState::LEVEL_SELECT)
        {
            DrawText(
                "LEVEL SELECT",
                GetScreenWidth() / 2 - 120,
                100,
                40,
                WHITE
            );

            DrawTexturePro(
                backButton,
                {0, 0, (float)backButton.width, (float)backButton.height},
                backRect,
                {0, 0},
                0,
                WHITE
            );

            for (int i = 0; i < levelCount; i++)
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
        else if (state == GameState::PLAYING)
        {
            DrawTexturePro(
                backButton,
                {0, 0, (float)backButton.width, (float)backButton.height},
                backRect,
                {0, 0},
                0,
                WHITE
            );

            if (currentLevel == 0)
            {
                DrawLineEx(
                    {0, groundY},
                    {(float)GetScreenWidth(), groundY},
                    4,
                    WHITE
                );

                DrawTexturePro(
                    cube,
                    {0, 0, (float)cube.width, (float)cube.height},
                    player,
                    {0, 0},
                    0,
                    WHITE
                );

                for (int i = 0; i < spikeCount; i++)
                {
                    float spikeX = spikes[i].x - levelOffset;

                    DrawTriangle(
                        {spikeX, groundY},
                        {spikeX + 20, groundY - 40},
                        {spikeX + 40, groundY},
                        RED
                    );
                }
            }
            else
            {
                DrawText(
                    levels[currentLevel].name,
                    GetScreenWidth() / 2 - MeasureText(levels[currentLevel].name, 40) / 2,
                    100,
                    40,
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
    UnloadTexture(cube);

    CloseWindow();
}