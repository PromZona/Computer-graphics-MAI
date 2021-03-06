#include <stdio.h>
#include "main.h"

int main(void)
{
    // Recommended window size
    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Polar coordinate plot. Essaulov Andrew");
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