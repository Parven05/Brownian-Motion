#include "particle.h"
#include "raymath.h"
#include <random>

Particle::Particle() : radius(10), position({ 0,0 }), velocity({0,0}), color(WHITE), mass(2), active(false) {};

void Particle::RandomInitialization(int totalCells, Particle* particles) const
{
	static std::mt19937 rng(static_cast<unsigned>(time(0)));
	static std::uniform_real_distribution<float> distPosX(0.0f, static_cast<float>(GetScreenWidth()));
	static std::uniform_real_distribution<float> distPosY(0.0f, static_cast<float>(GetScreenHeight()));
	static std::uniform_real_distribution<float> distVel(50.0f, 100.0f);

	for (int i = 0; i < totalCells; i++) {
		Particle& p = particles[i];
		p.position = { distPosX(rng), distPosY(rng) };
		p.velocity = { distVel(rng), distVel(rng) };
		p.active = true;

		if (i < 4) {
			p.radius = 40;
			static const Color colors[] = { GREEN, RED, BLUE, YELLOW };
			p.color = colors[i];
		}
	}
}

void Particle::Move(float dt)
{
	Vector2 gravity = { 0, 0 };

	// Brownian Motion Implementation
	static std::mt19937 rng(static_cast<unsigned>(time(0)));
	static std::uniform_real_distribution<float> dist(-0.5f, 0.5f);
	float sigma = 15.0f;
	Vector2 randomForce = {sigma * dist(rng), sigma * dist(rng)};

	Vector2 totalForce = Vector2Add(Vector2Scale(gravity, mass), randomForce);
	velocity = Vector2Add(velocity, Vector2Scale(totalForce, dt));
	position = Vector2Add(position, Vector2Scale(velocity, dt));

}