#include <stdio.h>
#include "main.h"

int main(void)
{

    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    app_t app;
    Init(&app, screenWidth, screenHeight, 100);
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        Input(&app);
        Update(&app);
        Render(&app);
    }

    CloseWindow(); // Close window and OpenGL context
    return 0;
}