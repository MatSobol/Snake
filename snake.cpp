#include "snake.hpp"
#include "math.hpp"
#include <cmath>
#include <iostream>
#include "rlgl.h"

#define TAIL_CIRCLES_NUM 9
#define MAX_ANGLE 10.0f
#define MAX_ANGLE_CHANGE 0.7f

void Snake::initialState(Vector2 startPos, int circleNum, float radius, float speed)
{
    Vector2 currPos = startPos;
    circles.clear();
    widths.clear();
    for (int i = 0; i < circleNum; i++)
    {
        float currWidth;
        if (i + TAIL_CIRCLES_NUM > circleNum)
        {
            currWidth = radius * (circleNum - i) / (TAIL_CIRCLES_NUM);
        }
        else
        {
            currWidth = radius;
        }
        widths.push_back(currWidth);
        circles.push_back(currPos);
        currPos.y += radius;
    }
    this->radius = radius;
    velocity = {0, speed};
}

Snake::Snake(Vector2 startPos, int circleNum, float radius, float speed)
{
    initialState(startPos, circleNum, radius, speed);
    head = LoadTexture("resources/head.png");
}

Snake::~Snake()
{
    UnloadTexture(head);
}

void Snake::eaten()
{
    auto end = circles.end();
    Vector2 direction = Vector2Sub(*(end - 1), *(end - 2));
    Normalize(direction);
    Vector2Scale(direction, radius);
    circles.push_back(Vector2Add(circles.back(), direction));
    widths.insert(widths.begin(), radius);
    circles.push_back(Vector2Add(circles.back(), direction));
    widths.insert(widths.begin(), radius);
}

std::vector<Vector2> Snake::move()
{
    float deltaTime = GetFrameTime();
    Vector2 timeVelocity = Vector2ScaleReturn(velocity, deltaTime);
    circles[0] = Vector2Sub(circles[0], timeVelocity);

    Vector2 delta = (Vector2){circles[1].x - circles[0].x, circles[1].y - circles[0].y};
    Normalize(delta);
    Vector2Scale(delta, radius);
    Vector2 newCirclePos = Vector2Add(circles[0], delta);
    circles[1] = newCirclePos;

    for (unsigned i = 2; i < circles.size(); i++)
    {
        Vector2 delta = (Vector2){circles[i].x - circles[i - 1].x, circles[i].y - circles[i - 1].y};
        Normalize(delta);
        Vector2Scale(delta, radius);
        Vector2 newCirclePos = Vector2Add(circles[i - 1], delta);
        circles[i] = newCirclePos;

        Vector2 firstVector = Vector2Sub(circles[i - 1], circles[i - 2]);
        Vector2 secondVector = Vector2Sub(circles[i], circles[i - 1]);

        float angle = Vector2Angle(firstVector, secondVector) * 180 / PI;

        if (angle > MAX_ANGLE || angle < -MAX_ANGLE)
        {
            Vector2Rotate(secondVector, std::max(-MAX_ANGLE_CHANGE, std::min(-(angle - MAX_ANGLE), MAX_ANGLE_CHANGE)));
            circles[i] = Vector2Add(circles[i - 1], secondVector);
        }
    }

    Vector2 headPos = NormalizeReturn(velocity);
    Vector2Scale(headPos, -SNAKE_CIRCLE_RADIUS - 10.0f);
    headPos.x += circles[0].x;
    headPos.y += circles[0].y;
    this->headPos = headPos;

    return circles;
}

std::array<Vector2, 2> Snake::getNeigbours(int index)
{
    Vector2 vector;
    if (index == 0)
    {
        vector = velocity;
    }
    else
    {
        vector = Vector2Sub(circles[index], circles[index - 1]);
    }

    Vector2 leftVector = (Vector2){-vector.y, vector.x};
    Vector2 rightVector = (Vector2){vector.y, -vector.x};

    Normalize(leftVector);
    Normalize(rightVector);
    Vector2Scale(leftVector, widths[index]);
    Vector2Scale(rightVector, widths[index]);
    leftVector = Vector2Add(circles[index], leftVector);
    rightVector = Vector2Add(circles[index], rightVector);
    std::array<Vector2, 2> result = {leftVector, rightVector};
    return result;
}

void Snake::leftTurn(float angle)
{
    float deltaTime = GetFrameTime();
    float timeAngle = angle * deltaTime;
    Vector2Rotate(velocity, -timeAngle);
}

void Snake::rightTurn(float angle)
{
    float deltaTime = GetFrameTime();
    float timeAngle = angle * deltaTime;
    Vector2Rotate(velocity, timeAngle);
}

void DrawGreenPolygon(std::vector<std::array<Vector2, 2>> &points)
{
    Texture2D dummyTexture = {0};
    rlSetTexture(dummyTexture.id);

    rlColor4ub(0, 255, 0, 255);

    rlBegin(RL_TRIANGLES);

    for (unsigned i = 0; i < points.size() - 1; i++)
    {
        rlVertex2f(points[i][0].x, points[i][0].y);
        rlVertex2f(points[i + 1][0].x, points[i + 1][0].y);
        rlVertex2f(points[i][1].x, points[i][1].y);

        rlVertex2f(points[i][1].x, points[i][1].y);
        rlVertex2f(points[i + 1][0].x, points[i + 1][0].y);
        rlVertex2f(points[i + 1][1].x, points[i + 1][1].y);
    }

    rlEnd();

    rlSetTexture(0);
}

void Snake::drawSnake()
{
    std::vector<std::array<Vector2, 2>> points;

    for (unsigned i = 0; i < circles.size(); i++)
    {
        std::array<Vector2, 2> neighbors = getNeigbours(i);
        points.push_back(neighbors);
    }

    DrawGreenPolygon(points);

    float degree = atan2f(velocity.y, velocity.x) * 180 / PI;

    DrawTexturePro(
        head,
        (Rectangle){0, 0, (float)head.width, (float)head.height},
        (Rectangle){headPos.x, headPos.y, (float)head.width, (float)head.height},
        (Vector2){(float)head.width / 2.0f, (float)head.height / 2.0f},
        180.0f + degree,
        WHITE);
}