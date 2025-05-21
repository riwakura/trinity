# TRINITY -- Three-body Radau IAS15 Numerical Integrator for Trajectory dYnamics

TRNITY is a numerical integration code dedicated to hierarchical three-body systems.
By adopting a coordinate system with the inner center of mass as the origin and using IAS15 (Rein & Spiegel 2015) for time integration, the round-off errors in the integration are reduced to an extremely small level.

## Features

* **Model**: Hierarchical triple system (inner binary + a third outer body).
* **Coordinate System**: Frame of reference with the origin at the center of mass of the inner binary (CoM(inner)).
* **Integrator**: Custom IAS15 implementation (currently a stub).
* **Orbital Element Calculation**: Computes semi-major axes for the inner and outer orbits to assess orbital stability.
* **Termination Condition**: The simulation stops if the ratio of the inner to outer semi-major axes changes by 10% or more from its initial value.
* **Code Structure**: Modular C++ code organized by functionality (`Vec3D`, `Particle`, `OdeFunctions`, `IAS15Integrator`, `OrbitalElements`, `main`).

## Current Status

* **Under active development.**
* The basic simulation framework (initial condition setup, definition of equations of motion, orbital element calculation, termination condition logic) is in place.
* The core logic of the IAS15 integrator (within the `step` function) is currently a basic Euler method stub for operational testing. This will be replaced with the full IAS15 algorithm in the future.

## Code Structure

The project is composed of the following main modules (sets of files):

* **`Vec3D.h`, `Vec3D.cpp`**: Basic class for 3D vector operations.
* **`Particle.h`, `Particle.cpp`**: Struct to store physical information of particles (celestial bodies), such as mass, position, velocity, and acceleration.
* **`OdeFunctions.h`, `OdeFunctions.cpp`**: Defines the equations of motion for the system being simulated (`hierarchical_triple_ode`).
* **`IAS15Integrator.h`, `IAS15Integrator.cpp`**: Class for the IAS15 integrator (currently a stub). Responsible for time evolution.
* **`OrbitalElements.h`, `OrbitalElements.cpp`**: Collection of functions to calculate orbital elements like semi-major axes.
* **`main.cpp`**: Contains the main simulation loop, initialization, integrator calls, termination condition management, result display, etc.

## How to Build

A C++17 compliant compiler (g++ or clang++ recommended) is required.
Compile and link all `.cpp` files using the following commands to generate the executable `trinity_sim`.

**Using g++:**
```bash
g++ -std=c++17 main.cpp Vec3D.cpp Particle.cpp OdeFunctions.cpp IAS15Integrator.cpp OrbitalElements.cpp -o trinity_sim
```

**Using MacOS:**
```bash
clang++ -std=c++17 main.cpp Vec3D.cpp Particle.cpp OdeFunctions.cpp IAS15Integrator.cpp OrbitalElements.cpp -o trinity_sim
```
