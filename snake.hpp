#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"
#include <vector>
#include <array>

#define STARTING_CIRCLE_NUM 30

#define LEfT_TURN_SPEED 120.0f
#define RIGHT_TURN_SPEED 120.0f
#define DEFAULT_SPEED 430.0f

#define SNAKE_CIRCLE_RADIUS 30.0f
#define SNAKE_HEAD_CRICLE_SIZE 45.0f

class Snake
{
public:
    Vector2 velocity;
    std::vector<float> widths;
    std::vector<Vector2> circles;
    Vector2 headPos;

    Snake(Vector2 startPos, int circleNum, float radius, float speed);
    ~Snake();
    void initialState(Vector2 startPos, int circleNum, float radius, float speed);
    std::vector<Vector2> move();
    void leftTurn(float angle);
    void rightTurn(float angle);
    std::array<Vector2, 2> getNeigbours(int index);
    void drawSnake();
    void eaten();

private:
    float radius;
    Texture2D head;
};

#endif
