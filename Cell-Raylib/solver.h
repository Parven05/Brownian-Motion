#include "particle.h"

struct Solver
{
	void WindowCollision(Particle& particle);
	void CircleCollision(Particle& a, Particle& b);
};