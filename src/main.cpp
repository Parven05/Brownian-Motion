#include "solver.h"

void static Window() 
{
	const int width = 800;
	const int height = 800;
	SetTargetFPS(60);
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	InitWindow(width, height, "Brownian Motion");
}

void static Simulate(int totalCells, Particle* particles, Solver& solver, float deltaTime) 
{
	for (int i = 0; i < totalCells; ++i) {  // Access each particle 
		Particle& p1 = particles[i];
		if (p1.active) { // Check each particle is render
			p1.Move(deltaTime); // Apply Brownian Motion
			DrawCircle(p1.position.x, p1.position.y, p1.radius, p1.color); // Draw each particle in window
			solver.WindowCollision(p1); // Apply window collision logic for each particle

			// Resolve circle collision
			for (int j = i + 1; j < totalCells; ++j) {
				Particle& p2 = particles[j];
				if (p2.active) {
					if (CheckCollisionCircles(p2.position, p2.radius, p2.position, p2.radius)) {
						solver.CircleCollision(p2, p1);
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
	Particle* particles = new Particle[totalCells];
	particles->RandomInitialization(totalCells,particles); // Initialize random Vector2 values for each of the particle
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
	delete[] particles;
	CloseWindow();
};

