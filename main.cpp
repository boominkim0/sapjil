#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Simple Bouncing Ball Game");
    SetTargetFPS(60);

    Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };
    Vector2 ballSpeed = { 5.0f, 4.0f };
    float ballRadius = 20;

    while (!WindowShouldClose()) {
        // Update
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            ballSpeed.x = GetRandomValue(-10, 10);
            ballSpeed.y = GetRandomValue(-10, 10);
        }

        ballPosition.x += ballSpeed.x;
        ballPosition.y += ballSpeed.y;

        if ((ballPosition.x >= (screenWidth - ballRadius)) || (ballPosition.x <= ballRadius)) ballSpeed.x *= -1.0f;
        if ((ballPosition.y >= (screenHeight - ballRadius)) || (ballPosition.y <= ballRadius)) ballSpeed.y *= -1.0f;

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Simple Bouncing Ball Game", 10, 10, 20, DARKGRAY);
        DrawCircleV(ballPosition, ballRadius, MAROON);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}