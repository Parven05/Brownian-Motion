#include "particle.h"

float Particle::restitution = 1.0f;

Particle::Particle() : radius(10), position({ 0,0 }), velocity({0,0}), color(WHITE), mass(2), active(false) {};

void Particle::Move(float dt)
{
    Vector2 gravity = { 0, 0 };

    // Brownian Motion Implementation
    float sigma = 15.0f;
    Vector2 randomForce = {
        sigma * (GetRandomValue(0, RAND_MAX) / (float)RAND_MAX - 0.5f),
        sigma * (GetRandomValue(0, RAND_MAX) / (float)RAND_MAX - 0.5f)
    };

    Vector2 totalForce = Vector2Add(Vector2Scale(gravity, mass), randomForce);
    velocity = Vector2Add(velocity, Vector2Scale(totalForce, dt));
    position = Vector2Add(position, Vector2Scale(velocity, dt));

}

void Particle::RandomInitialization(int totalCells, Particle particles[]) const
{
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
}