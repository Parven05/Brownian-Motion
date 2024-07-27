#pragma once

#include "raylib.h"

struct Particle
{
	Particle();
	void RandomInitialization(int totalCells, Particle* particles) const;
	void Move(float dt);

	int radius;
	Vector2 position;
	Vector2 velocity;
	Color color;
	bool active;
	float mass;
};
