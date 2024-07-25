#include "solver.h"

int main()
{
	// WINDOW -----------------------------------------------------------------------------
	const int width = 800;
	const int height = 800;
	
	SetTargetFPS(60);

	SetConfigFlags(FLAG_MSAA_4X_HINT);

	InitWindow(width, height, "Cell");

	//-------------------------------------------------------------------------------------

	const int totalCells = 500;

	Particle particles[totalCells];
	Solver solver;

	srand(static_cast<unsigned>(time(0)));

	for (int i = 0; i < totalCells; i++)
	{
		particles[i].position = Vector2{
			static_cast<float>(rand() % GetScreenWidth()),
			static_cast<float>(rand() % GetScreenHeight())
		};
		particles[i].velocity = Vector2{
			static_cast<float>(rand() % (200 - 100 + 1) + 100),
			static_cast<float>(rand() % (200 - 100 + 1) + 100)
		};
		particles[i].active = true;

		if (i == 1)
		{
			particles[i].radius = 40;
			particles[i].color = GREEN;
		}

		else if (i == 2)
		{
			particles[i].radius = 40;
			particles[i].color = YELLOW;
		}

		else if (i == 3)
		{
			particles[i].radius = 40;
			particles[i].color = BLUE;
		}

		else if (i == 4)
		{
			particles[i].radius = 40;
			particles[i].color = RED;
		}
	}

	// EVENT -----------------------------------------------------------------------------

	while (!WindowShouldClose())
	{
		const float deltaTime = GetFrameTime();

		ClearBackground(Color{ 17,11,17, 255});

		for (int i = 0; i < totalCells; ++i)
		{
			if (particles[i].active)
			{
				particles[i].Move(deltaTime);
				DrawCircle(particles[i].position.x, particles[i].position.y, particles[i].radius, particles[i].color);
				solver.WindowCollision(particles[i]);
				
				for (int j = i + 1; j < totalCells; ++j)
				{
					if (particles[j].active)
					{
						if (CheckCollisionCircles(particles[j].position, particles[j].radius, particles[i].position, particles[i].radius))
						{
							solver.CircleCollision(particles[j], particles[i]);
						}
					}
				}

			}
			
		}

		DrawFPS(5,5);

		EndDrawing();
	}

	CloseWindow();
};

