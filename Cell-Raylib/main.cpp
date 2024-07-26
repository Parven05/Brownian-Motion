#include "solver.h"

void Window()
{
	const int width = 800;
	const int height = 800;
	SetTargetFPS(60);
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	InitWindow(width, height, "Brownian Motion");
}

void Simulate(int totalCells, Particle* particles, Solver& solver, float deltaTime)
{
	for (int i = 0; i < totalCells; ++i) // Access each particle
	{
		if (particles[i].active) // Check each particle is render
		{
			particles[i].Move(deltaTime); // Apply Brownian Motion
			DrawCircle(particles[i].position.x, particles[i].position.y, particles[i].radius, particles[i].color); // Draw each particle in window
			solver.WindowCollision(particles[i]); // Apply window collision logic for each particle

			for (int j = i + 1; j < totalCells; ++j) // Access each particle again
			{
				if (particles[j].active) // Check if the particle is render
				{
					if (CheckCollisionCircles(particles[j].position, particles[j].radius, particles[i].position, particles[i].radius)) // Check collision of particles themself
					{
						solver.CircleCollision(particles[j], particles[i]); // Apply circle collision physics to particles
					}
				}
			}

		}

	}
}

int main()
{
	// START ------------------------------------------------------------------------------
	Window();
	Solver solver;
	const int totalCells = 500;	// Number of total particles
	Particle particles[totalCells]; // Each particle in an array
	particles->RandomInitialization(totalCells,particles); // Initialize random Vector2 values for each of the particle
	srand(static_cast<unsigned>(time(0)));
	//-------------------------------------------------------------------------------------
	// LOOP -------------------------------------------------------------------------------
	while (!WindowShouldClose())
	{
		const float deltaTime = GetFrameTime();
		ClearBackground(BLACK);
		BeginDrawing();
		Simulate(totalCells, particles, solver, deltaTime);
		DrawFPS(5,5);
		EndDrawing();
	}
	//-------------------------------------------------------------------------------------
	CloseWindow();
};

