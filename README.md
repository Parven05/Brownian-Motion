![Status](https://badgen.net/badge/Status/Experiment/orange?icon=github)
![Engine](https://badgen.net/badge/Engine/Raylib/blue)
![License](https://badgen.net/badge/license/MIT/green)

## **Brownian Motion**
![brownian](https://github.com/user-attachments/assets/e1ea43fd-0d4c-464c-8200-1a6b86bf6f10)

```math
1. \quad \mathbf{F}_{\text{random}} = \text{RandomGaussian}(0, \sigma)

2. \quad \mathbf{F}_{\text{total}} = m \cdot \mathbf{g} + \mathbf{F}_{\text{random}}

3. \quad \mathbf{v} = \mathbf{v} + \frac{\mathbf{F}_{\text{total}}}{m} \cdot \Delta t

4. \quad \mathbf{x} = \mathbf{x} + \mathbf{v} \cdot \Delta t
```
