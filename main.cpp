#include "raylib.h"
#include "math.hpp"
#include "snake.hpp"

#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#define DEFAULTWIDTH 1920
#define DEFAULTHEIGHT 1080
#define WALL_SIZE 17
#define WALL_OFFSET 40

#define PI 3.14159265358979323846f

const Vector2 virtualSize = {1920, 1080};
int score = 0;
bool isLost = false;

void toggleFullScreen(Vector2 *windowSize)
{
	if (!IsWindowFullscreen())
	{
		int monitor = GetCurrentMonitor();
		windowSize->x = GetMonitorWidth(monitor);
		windowSize->y = GetMonitorHeight(monitor);
		SetWindowSize(windowSize->x, windowSize->y);
		ToggleFullscreen();
	}
	else
	{
		windowSize->x = DEFAULTWIDTH;
		windowSize->y = DEFAULTHEIGHT;
		ToggleFullscreen();
		SetWindowSize(DEFAULTWIDTH, DEFAULTHEIGHT);
	}
}

void setApplePos(Vector2 &applePos, Texture2D apple)
{
	applePos.x = rand() % ((int)virtualSize.x - 2 * WALL_SIZE - apple.width - WALL_OFFSET) + WALL_SIZE;
	applePos.y = rand() % ((int)virtualSize.y - 2 * WALL_SIZE - apple.height - WALL_OFFSET) + WALL_SIZE;
}

bool ifEaten(Vector2 applePos, Texture2D apple, Vector2 headPos)
{
	applePos.x += apple.width / 2;
	applePos.y += apple.height / 2;
	Vector2 diff = Vector2Sub(applePos, headPos);
	if (abs(diff.x) < SNAKE_HEAD_CRICLE_SIZE && abs(diff.y) < SNAKE_HEAD_CRICLE_SIZE)
		return true;
	return false;
}

void collision(Vector2 &applePos, Texture2D apple, Snake &snake)
{
	if (snake.headPos.x < 17 || snake.headPos.x > DEFAULTWIDTH - 17 || snake.headPos.y < 17 || snake.headPos.y > DEFAULTHEIGHT - 17)
	{
		isLost = true;
		return;
	}

	for (unsigned i = 1; i < snake.circles.size(); i++)
	{
		Vector2 diff = Vector2Sub(snake.circles[i], snake.headPos);
		if (abs(diff.x) < snake.widths[i] && abs(diff.y) < snake.widths[i])
		{
			isLost = true;
			return;
		}
	}

	if (ifEaten(applePos, apple, snake.headPos))
	{
		setApplePos(applePos, apple);
		score++;
		snake.eaten();
	}
}

int main()
{
	Vector2 windowSize = {DEFAULTWIDTH, DEFAULTHEIGHT};
	InitWindow(DEFAULTWIDTH, DEFAULTHEIGHT, "Snake");
	RenderTexture2D target = LoadRenderTexture(virtualSize.x, virtualSize.y);
	SetTargetFPS(100);

	Texture2D background = LoadTexture("resources/background.png");
	Texture2D apple = LoadTexture("resources/apple.png");

	Vector2 snakeStartPos = {virtualSize.x / 2, virtualSize.y / 2};
	Snake snake(snakeStartPos, STARTING_CIRCLE_NUM, SNAKE_CIRCLE_RADIUS, DEFAULT_SPEED);

	Vector2 applePos = {0, 0};
	setApplePos(applePos, apple);

	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_F11))
		{
			toggleFullScreen(&windowSize);
		}
		if (IsKeyDown(KEY_A))
		{
			snake.leftTurn(LEfT_TURN_SPEED);
		}
		if (IsKeyDown(KEY_D))
		{
			snake.rightTurn(RIGHT_TURN_SPEED);
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			isLost = false;
			score = 0;
			snake.initialState(snakeStartPos, STARTING_CIRCLE_NUM, SNAKE_CIRCLE_RADIUS, DEFAULT_SPEED);
		}

		if (isLost)
		{
			BeginTextureMode(target);
			ClearBackground(DARKGREEN);
			DrawText("GAME OVER", virtualSize.x / 2 - 250, virtualSize.y / 2 - 100, 80, BLACK);
			DrawText("click left mouse button", virtualSize.x / 2 - 300, virtualSize.y / 2, 50, BLACK);
			EndTextureMode();
		}
		else
		{
			BeginTextureMode(target);

			std::vector<Vector2> circles = snake.move();
			collision(applePos, apple, snake);

			DrawTexture(background, 0, 0, WHITE);
			DrawTexture(apple, applePos.x, applePos.y, WHITE);

			snake.drawSnake();

			DrawText(std::to_string(score).c_str(), virtualSize.x / 2, 40, 100, BLACK);

			EndTextureMode();
		}
		BeginDrawing();
		DrawTexturePro(
			target.texture,
			(Rectangle){0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height},
			(Rectangle){0.0f, 0.0f, (float)windowSize.x, (float)windowSize.y},
			(Vector2){0.0f, 0.0f},
			0.0f,
			WHITE);
		EndDrawing();
	}

	UnloadRenderTexture(target);
	CloseWindow();
	return 0;
}
