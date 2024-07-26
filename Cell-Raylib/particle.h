#include "iostream"
#include "raylib.h"
#include "raymath.h"

class Particle
{
public:
	Particle();
	void Move(float dt);
	void RandomInitialization(int totalCells, Particle particles[]) const;

public:
	int radius;
	Vector2 position;
	Vector2 velocity;
	bool active;
	Color color;
	float mass;
	static float restitution;
};