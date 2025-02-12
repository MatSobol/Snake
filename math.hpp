#ifndef MATH_H
#define MATH_H

#include "raylib.h"

Vector2 Vector2Add(Vector2 first, Vector2 second);
Vector2 Vector2Sub(Vector2 first, Vector2 second);
void Vector2Scale(Vector2 &first, float scale);
Vector2 Vector2ScaleReturn(Vector2 vec, float angle);
void Vector2Rotate(Vector2 &vec, float angle);
void Normalize(Vector2 &vec);
Vector2 NormalizeReturn(Vector2 vec);
float Vector2Angle(const Vector2 first, const Vector2 second);

#endif
