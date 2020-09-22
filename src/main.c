#include <stdio.h>
#include "raylib.h"
#include "raymath.h"

void Input()
{
}

void Update()
{
}

void Render()
{
    double iterationStep = 0.005;
    double userConst = 100;
    BeginDrawing();

    ClearBackground(RAYWHITE);
    for (double i = 0; i < PI; i += iterationStep)
    {
        float r = userConst * cosf(3 * i); // r = a * cos(a*f)
        float x = r * cosf(i);
        float y = r * sinf(i);

        DrawCircle((int)x + 400, (int)y + 225, 1, RED);
    }
    DrawFPS(10, 10);
    EndDrawing();
}

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        Input();
        Update();
        Render();
    }

    CloseWindow(); // Close window and OpenGL context
    return 0;
}