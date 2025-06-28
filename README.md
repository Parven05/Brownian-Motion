![Status](https://badgen.net/badge/Status/Experiment/orange?icon=github)
![Engine](https://badgen.net/badge/Engine/Raylib/blue)
![License](https://badgen.net/badge/license/MIT/green)

## **Brownian Motion**
![brownian](https://github.com/user-attachments/assets/e1ea43fd-0d4c-464c-8200-1a6b86bf6f10)

This project simulates Brownian motion using 2D particles in C++ with raylib. Each particle moves randomly by applying small forces every frame, creating jittery, natural motion. There's no gravity movement is driven entirely by random forces, making it ideal for visualizing microscopic particle behavior.

## **Implementation**

```math
1. \quad \mathbf{F}_{\text{random}} = \text{RandomGaussian}(0, \sigma)
```
```c++
    float sigma = 15.0f;
    float randX = sigma * (GetRandomValue(-50, 50) / 100.0f);  // ~ [-7.5, 7.5]
    float randY = sigma * (GetRandomValue(-50, 50) / 100.0f);
    Vector2 randomForce = { randX, randY };
```
This code simulates a random force by scaling a uniformly distributed value into a small float range. It approximates Gaussian noise by generating values between -7.5 and 7.5, creating the jittery effect typical of Brownian motion.

```math
2. \quad \mathbf{F}_{\text{total}} = m \cdot \mathbf{g} + \mathbf{F}_{\text{random}}
```
```c++
    // Gravity is 0 for now (can be replaced with {0, 9.8f} later)
    Vector2 gravity = { 0, 0 };
    Vector2 totalForce = Vector2Add(Vector2Scale(gravity, mass), randomForce);
```
This code calculates the **total force** on the particle.
Since gravity is set to zero, the total force equals just the random force. However, the formula still includes `m * g + F_random` to keep it flexible if gravity is added later.

```math
3. \quad \mathbf{v} = \mathbf{v} + \frac{\mathbf{F}_{\text{total}}}{m} \cdot \Delta t
4. \quad \mathbf{x} = \mathbf{x} + \mathbf{v} \cdot \Delta t
```
```c++
    // Apply Verlet Integration
    Vector2 acceleration = Vector2Scale(totalForce, 1.0f / mass);
    velocity = Vector2Add(velocity, Vector2Scale(acceleration, dt));
    position = Vector2Add(position, Vector2Scale(velocity, dt));
```
This code updates the particle's velocity and position using Verlet Integration.

