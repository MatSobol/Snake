#include "math.hpp"
#include <cmath>

Vector2 Vector2Sub(Vector2 first, Vector2 second)
{
    return (Vector2){first.x - second.x, first.y - second.y};
}

Vector2 Vector2Add(Vector2 first, Vector2 second)
{
    return (Vector2){first.x + second.x, first.y + second.y};
}

void Vector2Scale(Vector2 &first, float scale)
{
    first.x = first.x * scale;
    first.y = first.y * scale;
}

void Normalize(Vector2 &vec)
{
    float magnitude = sqrtf(vec.x * vec.x + vec.y * vec.y);
    if (magnitude == 0.0f)
        return;
    Vector2Scale(vec, 1 / magnitude);
}

Vector2 NormalizeReturn(Vector2 vec)
{
    Normalize(vec);
    return vec;
}

Vector2 Vector2ScaleReturn(Vector2 vec, float scale)
{
    Vector2Scale(vec, scale);
    return vec;
}

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