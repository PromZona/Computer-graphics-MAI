#include "app.h"

#define MAX_POINTS_COUNT 1024
#define UNIT 10

typedef struct app_s
{
    int width;  // Screen wide
    int height; // Screen high

    double iteration_step; // accuracy of line. Less value -> more point -> more smooth
    double user_value;     // user value to modify plot function

    Vector2 shift;

    int points_count;
    Vector2 points[MAX_POINTS_COUNT];
} app_t;

double iterationCalc(double user_value)
{
    return 6 / user_value;
}

void Init(app_t *app, int w, int h, double user_start)
{
    app->width = w;
    app->height = h;

    app->user_value = user_start;
    app->iteration_step = iterationCalc(app->user_value);

    app->shift.x = w / 2;
    app->shift.y = h / 2;

    app->points_count = 0;
}

void Input(app_t *app)
{
    if (IsKeyPressed(KEY_KP_ADD))
    {
        if (app->points_count < MAX_POINTS_COUNT)
        {
            app->user_value += UNIT;
            app->iteration_step = iterationCalc(app->user_value);
        }
    }

    if (IsKeyPressed(KEY_KP_SUBTRACT))
    {
        if (app->points_count > UNIT)
        {
            app->user_value -= 5;
            app->iteration_step = iterationCalc(app->user_value);
        }
    }

    if (IsKeyPressed(KEY_UP))
    {
        app->shift.y += UNIT;
    }

    if (IsKeyPressed(KEY_DOWN))
    {
        app->shift.y -= UNIT;
    }

    if (IsKeyPressed(KEY_RIGHT))
    {
        app->shift.x -= UNIT;
    }

    if (IsKeyPressed(KEY_LEFT))
    {
        app->shift.x += UNIT;
    }
}

void Update(app_t *app)
{
    app->points_count = 0;
    for (double i = -PI; i < PI; i += app->iteration_step)
    {
        float r = app->user_value * cosf(3 * i); // r = a * cos(a*f)
        float x = r * cosf(i);
        float y = r * sinf(i);

        if (app->points_count <= MAX_POINTS_COUNT - 1)
        {
            app->points[app->points_count].x = x + app->shift.x;
            app->points[app->points_count].y = y + app->shift.y;
            app->points_count++;
        }
    }
    app->points[app->points_count] = app->points[0];
    app->points_count++;
}

void Render(app_t *app)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawLine(0, app->shift.y, app->width, app->shift.y, BLUE);  // AXIS X
    DrawLine(app->shift.x, 0, app->shift.x, app->height, BLUE); // AXIS Y

    for (int x = 0; x < app->width; x += UNIT)
    {
        if ((x / 10) % 2  == 0)
        {
            DrawLineEx((Vector2){x, 0}, (Vector2){x, app->height}, 1.0f, LIGHTGRAY); // Grid
        }
        DrawLine(x, app->shift.y - 3, x, app->shift.y + 3, BLUE); // Measure
    }

    for (int y = 0; y < app->height; y += UNIT)
    {
        if ((y / 10) % 2 == 0)
        {
            DrawLineEx((Vector2){0, y}, (Vector2){app->width, y}, 1.0f, LIGHTGRAY); // Grid
        }
        DrawLine(app->shift.x - 3, y, app->shift.x + 3, y, BLUE); // Measure
    }

    DrawLineStrip(app->points, app->points_count, RED); // Plot

    char str[16];
    sprintf(str, "Points - %d", app->points_count);
    DrawText(str, UNIT, 40, 18, DARKGREEN);

    DrawFPS(10, 10);
    EndDrawing();
}