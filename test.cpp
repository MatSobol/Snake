#include "raylib.h"

#include <cmath>
#include <iostream>

#define PI 3.14159265358979323846f

float Vector2Angle(const Vector2 first, const Vector2 second)
{
    float dot = first.x * second.x + first.y * second.y;
    float det = first.x * second.y - first.y * second.x;
    float angle = atan2(det, dot);
    return angle;
}

void Vector2Rotate(Vector2 &vec, float angle)
{
    float theta = angle * PI / 180;

    float cs = cos(theta);
    float sn = sin(theta);

    float px = vec.x * cs - vec.y * sn;
    float py = vec.x * sn + vec.y * cs;

    vec.x = px;
    vec.y = py;
}

int main()
{
    InitWindow(1920, 1080, "Snake");
    Vector2 first = (Vector2){300.0f, 0.0f};
    Vector2 second = (Vector2){0.0f, 300.0f};

    float angle = Vector2Angle(first, second) * 180 / PI;

    Vector2Rotate(second, -(angle - 45.0f));

    Vector2 firstStart = (Vector2){1000.0f, 540.0f};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        Vector2 curr = (Vector2){firstStart.x + first.x, firstStart.y + first.y};
        DrawLineV(firstStart, curr, RED);
        Vector2 curr2 = (Vector2){firstStart.x + second.x, firstStart.y + second.y};
        DrawLineV(firstStart, curr2, GREEN);
        EndDrawing();
    }
}