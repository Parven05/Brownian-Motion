#include "solver.h"
#include "imgui.h"
#include "rlImGui.h"

int main()
{
	// WINDOW -----------------------------------------------------------------------------
	const int width = 800;
	const int height = 800;
	
	SetTargetFPS(60);

	SetConfigFlags(FLAG_MSAA_4X_HINT);

	InitWindow(width, height, "Cell");
	
	rlImGuiSetup(true);

	//-------------------------------------------------------------------------------------

	const int totalCells = 500;

	Particle particles[totalCells];
	Solver solver;

	int temperature = 0.0f;

	srand(static_cast<unsigned>(time(0)));

	for (int i = 0; i < totalCells; i++)
	{
		particles[i].position = Vector2{
			static_cast<float>(rand() % GetScreenWidth()),
			static_cast<float>(rand() % GetScreenHeight())
		};
		particles[i].velocity = Vector2{
			static_cast<float>(rand() % (temperature - 100 + 1) + 100),
			static_cast<float>(rand() % (temperature - 100 + 1) + 100)
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

		particles[i].startPosition = particles[i].position;
	}

	// EVENT -----------------------------------------------------------------------------

	while (!WindowShouldClose())
	{
		const float deltaTime = GetFrameTime();

		ClearBackground(Color{ 17,11,17, 255});

		BeginDrawing();	

		rlImGuiBegin();
		ImGui::SetNextWindowPos(ImVec2(0, 700));
		ImGui::SetNextWindowSize(ImVec2(280, 100));
		ImGui::Begin("Simulation Parameters", nullptr, ImGuiWindowFlags_NoResize);

		ImGui::Text("FPS: %d", GetFPS());
		ImGui::SliderInt("Temperature", &temperature, 100, 200);

		for (int i = 0; i < totalCells; ++i)
		{
			if (particles[i].active)
			{
				particles[i].Move(deltaTime);
				DrawCircle(particles[i].position.x, particles[i].position.y, particles[i].radius, particles[i].color);
				solver.WindowCollision(particles[i]);

				if (particles[i].radius == 40)
				{
					DrawLineV(particles[i].startPosition, particles[i].position, particles[i].color);
				}
				
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

		ImGui::End();
		rlImGuiEnd();
		EndDrawing();
	}
	CloseWindow();

};

