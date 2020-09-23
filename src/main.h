#include "app.h"

#define MAX_POINTS_COUNT 1024

typedef struct app_s
{
    int width;  // Screen wide
    int height; // Screen high

    double iteration_step; // accuracy of line. Less -> more point -> more smooth
    double user_value;     // user value to modify plot function

    int points_count;
    Vector2 points[MAX_POINTS_COUNT];
} app_t;

double iterationCalc(double user_value)
{
    return 1 / (user_value / 2);
}

void Init(app_t *app, int w, int h, double user_start)
{
    app->width = w;
    app->height = h;
    app->user_value = user_start;
    app->iteration_step = iterationCalc(app->user_value);

    app->points_count = 0;
}

void Input(app_t *app)
{
    if (IsKeyPressed(KEY_KP_ADD))
    {
        app->user_value += 5;
        app->iteration_step = iterationCalc(app->user_value);
    }

    if (IsKeyPressed(KEY_KP_SUBTRACT))
    {
        app->user_value -= 5;
        app->iteration_step = iterationCalc(app->user_value);
    }
}

void Update(app_t *app)
{
    app->points_count = 0;
    for (double i = 0.1; i < PI; i += app->iteration_step)
    {
        float r = app->user_value * cosf(3 * i); // r = a * cos(a*f)
        float x = r * cosf(i);
        float y = r * sinf(i);

        if (app->points_count <= MAX_POINTS_COUNT - 1)
        {
            app->points[app->points_count].x = x + (GetScreenWidth() / 2);
            app->points[app->points_count].y = y + (GetScreenHeight() / 2);
        }
        app->points_count++;
    }
    app->points[app->points_count] = app->points[0];
    app->points_count++;
}

void Render(app_t *app)
{
    BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawLineStrip(app->points, app->points_count, RED);

        char str[16];
        sprintf(str, "Points - %d", app->points_count);
        DrawText(str, 10, 40, 18, DARKGREEN);
        DrawFPS(10, 10);
    EndDrawing();
}
