#include "raylib.h"
#include "raymath.h"
#include "iostream"

struct Cell {
	Vector2 position;
	Color color;
	bool active;
};


int main()
{
	const int width = 800;
	const int height = 800;
	const float deltaTime = GetFrameTime();

	SetConfigFlags(FLAG_MSAA_4X_HINT);

	InitWindow(width, height, "Cell");
	SetTargetFPS(60);

	const float mouseSensitivity = 5.0f;
	const int totalCells = 50;

	srand(static_cast<unsigned>(time(0)));

	Vector2 circlePos = Vector2{ 200, 200 };
	int circleRadius = 50;
	int cellRadius = 10;

	Cell cells[totalCells];

	for (int i = 0; i < totalCells; i++)
	{
		cells[i].position = Vector2{
			  static_cast<float>(rand() % (width - 100 + 1) + 100),
			  static_cast<float>(rand() % (height - 100 + 1) + 100)
		};

		cells[i].color = Color{
			static_cast<unsigned char>(rand() % 256),
			static_cast<unsigned char>(rand() % 256),
			static_cast<unsigned char>(rand() % 256),
			255
		};

		cells[i].active = true;
	}

	while (!WindowShouldClose())
	{
		ClearBackground(RAYWHITE);

		Vector2 mousePos = GetMousePosition();
		circlePos = Vector2MoveTowards(circlePos, mousePos, mouseSensitivity);

		BeginDrawing();

		DrawText("Raylib", 650, 740, 40, BLACK);
		DrawCircle(circlePos.x, circlePos.y, circleRadius, BLUE);

		for (int i = 0; i < totalCells; ++i)
		{
			if (cells[i].active)
			{
				DrawCircle(cells[i].position.x, cells[i].position.y, cellRadius, cells[i].color);

				if (CheckCollisionCircles(circlePos, circleRadius, cells[i].position, cellRadius))
				{
					cells[i].active = false;
					circleRadius += 1;
				}
			}
			
		}

		EndDrawing();
	}
	CloseWindow();

};