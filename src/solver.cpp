#include "solver.h"
#include "raymath.h"
#include <cmath>

void Solver::WindowCollision(Particle& particle) const
{
	// Check for collision with left and right walls
	if (particle.position.x - particle.radius < 0) {
		particle.position.x = particle.radius;
		particle.velocity.x = -particle.velocity.x;
	}
	else if (particle.position.x + particle.radius > GetScreenWidth()) {
		particle.position.x = GetScreenWidth() - particle.radius;
		particle.velocity.x = -particle.velocity.x;
	}

	// Check for collision with top and bottom walls
	if (particle.position.y - particle.radius < 0) {
		particle.position.y = particle.radius;
		particle.velocity.y = -particle.velocity.y;
	}
	else if (particle.position.y + particle.radius > GetScreenHeight()) {
		particle.position.y = GetScreenHeight() - particle.radius;
		particle.velocity.y = -particle.velocity.y;
	}
}

void Solver::CircleCollision(Particle& a, Particle& b) const
{
	Vector2 dxdy = Vector2Subtract(b.position, a.position);
	float distance = Vector2Length(dxdy);
	float totalRadius = a.radius + b.radius;

	if (distance < totalRadius) {
		// Calculate the collision angle
		float angle = atan2f(dxdy.y, dxdy.x);
		float sinAngle = sinf(angle);
		float cosAngle = cosf(angle);

		// Rotate the velocity vectors to the collision coordinate system
		float v1x = a.velocity.x * cosAngle + a.velocity.y * sinAngle;
		float v1y = a.velocity.y * cosAngle - a.velocity.x * sinAngle;
		float v2x = b.velocity.x * cosAngle + b.velocity.y * sinAngle;
		float v2y = b.velocity.y * cosAngle - b.velocity.x * sinAngle;

		// Apply 1D collision equation along the x-axis
		float restitution = 1.0f;
		float v1PrimeX = (v1x * (a.mass - b.mass) + 2 * b.mass * v2x) * restitution / (a.mass + b.mass);
		float v2PrimeX = (v2x * (b.mass - a.mass) + 2 * a.mass * v1x) * restitution / (a.mass + b.mass);

		// Rotate the velocities back to the original coordinate system
		a.velocity.x = v1PrimeX * cosAngle - v1y * sinAngle;
		a.velocity.y = v1PrimeX * sinAngle + v1y * cosAngle;
		b.velocity.x = v2PrimeX * cosAngle - v2y * sinAngle;
		b.velocity.y = v2PrimeX * sinAngle + v2y * cosAngle;

		// Adjust positions to prevent sticking
		float overlap = 0.5f * (totalRadius - distance + 1.0f);
		Vector2 displacement = Vector2Scale(dxdy, overlap / distance);
		a.position = Vector2Subtract(a.position, displacement);
		b.position = Vector2Add(b.position, displacement);
	}
}