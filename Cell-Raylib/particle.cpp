#include "particle.h"

float Particle::restitution = 1.0f;

Particle::Particle() = default;

void Particle::Move(float dt)
{
	Vector2 gravity = Vector2{ 0, 0 };
	mass = 2;

	//Brownian Motion
	float sigma = 15.0f;
	Vector2 randomForce = Vector2{
		sigma * (static_cast<float>(rand()) / RAND_MAX - 0.5f),
		sigma * (static_cast<float>(rand()) / RAND_MAX - 0.5f)

	};

	Vector2 totalForce = Vector2{ mass * gravity.x + randomForce.x, mass * gravity.y + randomForce.y};

	velocity.x += totalForce.x * dt;
	velocity.y += totalForce.y * dt;

	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
	
}