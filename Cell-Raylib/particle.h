#include "iostream"
#include "raylib.h"
#include "raymath.h"

class Particle
{
public:
	Particle();
	void Move(float dt);

public:
	int radius = 10;
	Color color = WHITE;
	Vector2 startPosition;
	Vector2 position;
	Vector2 velocity;
	float mass;
	bool active;
	static float restitution;
};