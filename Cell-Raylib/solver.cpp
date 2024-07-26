#include "solver.h"

void Solver::WindowCollision(Particle& particle) const
{
	// Check for collision with left and right walls
	if (particle.position.x - particle.radius < 0)
	{
		particle.position.x = particle.radius;
		particle.velocity.x = -particle.velocity.x;
	}
	else if (particle.position.x + particle.radius > GetScreenWidth())
	{
		particle.position.x = GetScreenWidth() - particle.radius;
		particle.velocity.x = -particle.velocity.x;
	}

	// Check for collision with top and bottom walls
	if (particle.position.y - particle.radius < 0)
	{
		particle.position.y = particle.radius;
		particle.velocity.y = -particle.velocity.y;
	}
	else if (particle.position.y + particle.radius > GetScreenHeight())
	{
		particle.position.y = GetScreenHeight() - particle.radius;
		particle.velocity.y = -particle.velocity.y;
	}
}

void Solver::CircleCollision(Particle& a, Particle& b) const
{
	Vector2 dxdy = Vector2{ b.position.x - a.position.x, b.position.y - a.position.y };
	float dx = dxdy.x;
	float dy = dxdy.y;
	float distance = std::sqrt(dx * dx + dy * dy);
	float totalRadius = a.radius + b.radius;

	if (distance < totalRadius)
	{
		// Calculate the collision angle
		float angle = std::atan2(dy, dx);

		// Rotate the velocity vectors to the collision coordinate system
		float v1x = a.velocity.x * std::cos(angle) + a.velocity.y * std::sin(angle);
		float v1y = a.velocity.y * std::cos(angle) - a.velocity.x * std::sin(angle);
		float v2x = b.velocity.x * std::cos(angle) + b.velocity.y * std::sin(angle);
		float v2y = b.velocity.y * std::cos(angle) - b.velocity.x * std::sin(angle);

		// Apply 1D collision equation along the x-axis
		float v1PrimeX = (v1x * (a.mass - b.mass) + 2 * b.mass * v2x) * a.restitution / (a.mass + b.mass);
		float v2PrimeX = (v2x * (b.mass - a.mass) + 2 * a.mass * v1x) * b.restitution / (a.mass + b.mass);

		// Rotate the velocities back to the original coordinate system
		a.velocity.x = v1PrimeX * std::cos(-angle) + v1y * std::sin(-angle);
		a.velocity.y = v1y * std::cos(-angle) - v1PrimeX * std::sin(-angle);
		b.velocity.x = v2PrimeX * std::cos(-angle) + v2y * std::sin(-angle);
		b.velocity.y = v2y * std::cos(-angle) - v2PrimeX * std::sin(-angle);

		// Adjust positions to prevent sticking
		float overlap = 0.5f * (totalRadius - distance + 1.0f);
		Vector2 displacement = Vector2{ overlap * std::cos(angle), overlap * std::sin(angle) };
		a.position = Vector2Subtract(a.position, Vector2Scale(displacement, 1.0f));
		a.position = Vector2Subtract(a.position, Vector2Scale(displacement, 1.0f));
		b.position = Vector2Add(b.position, Vector2Scale(displacement, 1.0f));
	}
}