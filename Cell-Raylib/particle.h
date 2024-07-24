#include "iostream"
#include "raylib.h"
#include "raymath.h"

class Particle
{
public:
	Particle();
	void Move(float dt);

public:
	int radius = 20;
	Color color = Color{ 238, 78, 78, 255 };
	Vector2 position;
	Vector2 velocity;
	float mass;
	bool active;
	static float restitution;
};