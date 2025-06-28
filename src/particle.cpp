#include "particle.h"
#include "raymath.h"

// Constructor: Sets default values for a particle
Particle::Particle()
    : radius(10), position({ 0, 0 }), velocity({ 0, 0 }), color(WHITE), mass(2), active(false) {
}


// Initializes a list of particles with random position and velocity
void Particle::RandomInitialization(int totalCells, Particle* particles) const
{
    for (int i = 0; i < totalCells; i++) {
        Particle& p = particles[i];

        // Random position within screen bounds
        p.position = {
            static_cast<float>(GetRandomValue(0, GetScreenWidth())),
            static_cast<float>(GetRandomValue(0, GetScreenHeight()))
        };

        // Random velocity in range [50.0, 100.0]
        float vx = static_cast<float>(GetRandomValue(5000, 10000)) / 100.0f;
        float vy = static_cast<float>(GetRandomValue(5000, 10000)) / 100.0f;
        p.velocity = { vx, vy };

        p.active = true;

        // First few particles are larger and colored
        if (i < 4) {
            p.radius = 40;
            static const Color colors[] = { GREEN, RED, BLUE, YELLOW };
            p.color = colors[i];
        }
    }
}


// Updates the particle's position and velocity using Brownian motion
void Particle::Move(float dt)
{
    float sigma = 15.0f;
    float randX = sigma * (GetRandomValue(-50, 50) / 100.0f);  // ~ [-7.5, 7.5]
    float randY = sigma * (GetRandomValue(-50, 50) / 100.0f);
    Vector2 randomForce = { randX, randY };

    Vector2 gravity = { 0, 0 };
    Vector2 totalForce = Vector2Add(Vector2Scale(gravity, mass), randomForce);
    Vector2 acceleration = Vector2Scale(totalForce, 1.0f / mass);
    velocity = Vector2Add(velocity, Vector2Scale(acceleration, dt));
    position = Vector2Add(position, Vector2Scale(velocity, dt));
}
