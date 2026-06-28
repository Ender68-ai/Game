#include "game.hpp"
#include "../external/raylib/src/raylib.h"
#include "levels/logic.hpp"
#include "levels/everyend.hpp"

extern Spike spikes_everyend[];
extern block blocks_everyend[];
extern EndRect endRect_everyend;
extern const int spikeCount_everyend;
extern const int blockCount_everyend;

// Remember to fix the damn blocks - Fixed top landing!

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
    SetTargetFPS(1039);

    Texture2D background = LoadTexture("../assets/bg3.png");
    Texture2D playButton = LoadTexture("../assets/playbutton.png");
    Texture2D logo = LoadTexture("../assets/logo.png");
    Texture2D backButton = LoadTexture("../assets/backbutton.png");
    Texture2D cube = LoadTexture("../assets/cube.png");
    Texture2D spike = LoadTexture("../assets/spike.png");
    Texture2D block = LoadTexture("../assets/block.png");

    GameState state = GameState::MENU;
    int currentLevel = -1;

    Level levels[] =
    {
        {"Stereo Madness", {0, 0, 300, 80}},
        {"Every End", {0, 0, 300, 80}}
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
    
    Rectangle playernao = {
        500.0f,
        groundY - 90.0f,    
        90.0f,  
        90.0f    
    };

    float velocityY = 0.0f;
    bool onGround = true;

    float levelOffset = 0.0f;
    const float scrollSpeed = 1.0f;

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

                    player.x = 400.0f;
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
                if ((IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_J) || IsKeyPressed(KEY_G)) && onGround)
                {
                    velocityY = -3000.0f;
                    onGround = false;
                }
                
                velocityY += 1.0f;
                player.y += velocityY;
                
                playernao.x = player.x + 5.0f; 
                playernao.y = player.y + 5.0f;

                if (player.y >= groundY - player.height)
                {
                    player.y = groundY - player.height;
                    velocityY = 0.0f;
                    onGround = true;
                }

                levelOffset += scrollSpeed;

                // SPIKES COLLISION
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

                // BLOCKS COLLISION
                for (int i = 0; i < blockCount; i++)
                {
                    Rectangle blockRect =
                    {
                        blocks[i].x - levelOffset,
                        blocks[i].y,
                        blocks[i].width,
                        blocks[i].height
                    };

                    if (CheckCollisionRecs(playernao, blockRect))
                    {
                        // FIXED: Check if falling and if the player's bottom edge is close to the block's top edge
                        float playerBottom = player.y + player.height;
                        if (velocityY >= 0.0f && (playerBottom - blockRect.y) <= 20.0f)
                        {
                            // Land safely on top
                            player.y = blockRect.y - player.height;
                            velocityY = 0.0f;
                            onGround = true;
                        }
                        else
                        {
                            // Hit the side or ceiling -> Crash!
                            player.y = groundY - player.height;
                            velocityY = 0.0f;
                            onGround = true;
                            levelOffset = 0.0f;
                        }
                    }
                }

                Rectangle endRec =
                {
                    endRect.x - levelOffset,
                    endRect.y,
                    endRect.width,
                    endRect.height
                };

                if (CheckCollisionRecs(player, endRec))
                {
                    state = GameState::LEVEL_SELECT;
                }
            }
            else if (currentLevel == 1)
            {
                if ((IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_J) || IsKeyPressed(KEY_G)) && onGround)
                {
                    velocityY = -3000.0f;
                    onGround = false;
                }

                velocityY += 1.0f;
                player.y += velocityY;
                
                playernao.x = player.x + 5.0f;
                playernao.y = player.y + 5.0f;

                if (player.y >= groundY - player.height)
                {
                    player.y = groundY - player.height;
                    velocityY = 0.0f;
                    onGround = true;
                }

                levelOffset += scrollSpeed;

                // SPIKES COLLISION
                for (int i = 0; i < spikeCount_everyend; i++)
                {
                    Rectangle spikeRect =
                    {
                        spikes_everyend[i].x - levelOffset,
                        spikes_everyend[i].y,
                        spikes_everyend[i].width,
                        spikes_everyend[i].height
                    };

                    if (CheckCollisionRecs(player, spikeRect))
                    {
                        player.y = groundY - player.height;
                        velocityY = 0.0f;
                        onGround = true;
                        levelOffset = 0.0f;
                    }
                }

                // BLOCKS COLLISION
                for (int i = 0; i < blockCount_everyend; i++)
                {
                    Rectangle blockRect =
                    {
                        blocks_everyend[i].x - levelOffset,
                        blocks_everyend[i].y,
                        blocks_everyend[i].width,
                        blocks_everyend[i].height
                    };

                    if (CheckCollisionRecs(playernao, blockRect)) 
                    {
                        // FIXED: Added identical safe landing logic for level 1
                        float playerBottom = player.y + player.height;
                        if (velocityY >= 0.0f && (playerBottom - blockRect.y) <= 20.0f)
                        {
                            player.y = blockRect.y - player.height;
                            velocityY = 0.0f;
                            onGround = true;
                        }
                        else
                        {
                            player.y = groundY - player.height;
                            velocityY = 0.0f;
                            onGround = true;
                            levelOffset = 0.0f;
                        }
                    }
                }

                Rectangle endRec =
                {
                    endRect_everyend.x - levelOffset,
                    endRect_everyend.y,
                    endRect_everyend.width,
                    endRect_everyend.height
                };

                if (CheckCollisionRecs(player, endRec))
                {
                    state = GameState::LEVEL_SELECT;
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

            if (currentLevel == 0 || currentLevel == 1) 
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
                
                // 1. Draw Spikes
                for (int i = 0; i < spikeCount; i++)
                {
                    float spikeX = spikes[i].x - levelOffset;
                    float drawWidth  = spikes[i].width * 2.0f;
                    float drawHeight = spikes[i].height * 2.0f;

                    DrawTexturePro(
                        spike,
                        {0, 0, (float)spike.width, (float)spike.height},
                        {
                            spikeX - (drawWidth - spikes[i].width) / 2.0f,
                            spikes[i].y - (drawHeight - spikes[i].height),
                            drawWidth,
                            drawHeight
                        },
                        {0, 0},
                        0,
                        WHITE
                    );

                    DrawRectangleLines(
                        spikeX,
                        spikes[i].y,
                        spikes[i].width,
                        spikes[i].height,
                        YELLOW
                    );
                }

                // 2. Draw Blocks
                for (int i = 0; i < blockCount; i++)
                {
                    float blockX = blocks[i].x - levelOffset;

                    DrawTexturePro(
                        block,
                        {0, 0, (float)block.width, (float)block.height},
                        {
                            blockX,
                            blocks[i].y,
                            blocks[i].width,
                            blocks[i].height
                        },
                        {0, 0},
                        0,
                        WHITE
                    );

                    DrawRectangleLines(
                        blockX,
                        blocks[i].y,
                        blocks[i].width,
                        blocks[i].height,
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
    UnloadTexture(spike);
    UnloadTexture(block);

    CloseWindow();
}