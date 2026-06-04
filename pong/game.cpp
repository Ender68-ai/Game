#include "game.hpp"
#include <raylib.h>

int player1_score = 0;
int player2_score = 0;

class Ball {
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw() {
        DrawCircle(x, y, radius, WHITE);
    }

    void ResetBall() {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        float speed_choices[2] = {-1.0f, 1.0f};
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];
    }

    void Update() {
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speed_y *= -1;
        }
        if (x + radius >= GetScreenWidth()) // player2 wins
        {
            player1_score++;
            ResetBall();
        }

        if (x - radius <= 0) {
            player2_score++;
            ResetBall();
        }
    }
};

// Single paddle type used for both players. The two players differ only in
// position and which keys move them, so we parameterize those at construction
// instead of duplicating the class.
class Paddle {
public:
    float x, y;
    float width, height;
    int speed;
    int up_key;
    int down_key;

    void Draw() {
        DrawRectangle(x, y, width, height, WHITE);
    }

    void Update() {
        if (IsKeyDown(up_key)) {
            y = y - speed;
        }
        if (IsKeyDown(down_key)) {
            y = y + speed;
        }
        if (y <= 0) {
            y = 0;
        }
        if (y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }
    }
};

Ball ball;
Paddle player1;
Paddle player2;

Color BgTEAL = {0, 128, 128, 125};
Color cGREEN = {0, 200, 0, 127};


void PongGame::run()
{
    const char* title = "Pong Juego";

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1200, 800, title);
    SetWindowMinSize(800, 600);
    SetWindowMaxSize(800, 600);

    SetTargetFPS(60);

    ball.radius = 20;
    ball.x = GetScreenWidth() / 2;
    ball.y = GetScreenHeight() / 2;
    ball.speed_x = 3;
    ball.speed_y = 3;

    // Left paddle: W/S keys.
    player1.x = 50;
    player1.y = GetScreenHeight() / 2 - 50;
    player1.width = 20;
    player1.height = 100;
    player1.speed = 5;
    player1.up_key = KEY_W;
    player1.down_key = KEY_S;

    // Right paddle: arrow keys.
    player2.x = GetScreenWidth() - 70;
    player2.y = GetScreenHeight() / 2 - 50;
    player2.width = 20;
    player2.height = 100;
    player2.speed = 5;
    player2.up_key = KEY_UP;
    player2.down_key = KEY_DOWN;

        while (!WindowShouldClose())
    {
        int currentWidth = GetScreenWidth();
        int currentHeight = GetScreenHeight();

        // Keep right paddle attached to right side
        player2.x = currentWidth - 70;

        // Update
        ball.Update();
        player1.Update();
        player2.Update();

        // Collisions
        if (CheckCollisionCircleRec(
                Vector2{ball.x, ball.y},
                ball.radius,
                Rectangle{player1.x, player1.y, player1.width, player1.height}))
        {
            ball.speed_x *= -1;
            ball.x = player1.x + player1.width + ball.radius;
        }

        if (CheckCollisionCircleRec(
                Vector2{ball.x, ball.y},
                ball.radius,
                Rectangle{player2.x, player2.y, player2.width, player2.height}))
        {
            ball.speed_x *= -1;
            ball.x = player2.x - ball.radius;
        }

        BeginDrawing();

        ClearBackground(BgTEAL);

        DrawLine(
            currentWidth / 2,
            0,
            currentWidth / 2,
            currentHeight,
            WHITE
        );

        DrawCircle(
            currentWidth / 2,
            currentHeight / 2,
            100,
            cGREEN
        );

        DrawRing(
            {
                currentWidth / 2.0f,
                currentHeight / 2.0f
            },
            40,
            50,
            0,
            360,
            256,
            WHITE
        );

        ball.Draw();
        player1.Draw();
        player2.Draw();

        DrawText(
            TextFormat("Player 1: %i", player1_score),
            50,
            50,
            20,
            WHITE
        );

        DrawText(
            TextFormat("Player 2: %i", player2_score),
            currentWidth - 200,
            50,
            20,
            WHITE
        );

        EndDrawing();
    }
    CloseWindow();
}
