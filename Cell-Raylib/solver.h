#include "particle.h"

struct Solver
{
	void WindowCollision(Particle& particle) const;
	void CircleCollision(Particle& a, Particle& b) const;
};