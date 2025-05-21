#ifndef ORBITAL_ELEMENTS_H
#define ORBITAL_ELEMENTS_H

#include "Particle.h"
#include <cmath>    // For std::sqrt, std::isinf, std::isnan
#include <limits>   // For std::numeric_limits

// Innerバイナリの軌道長半径
double calculate_semi_major_axis_inner(const Particle& p1, const Particle& p2, double G);

// Outerボディの軌道長半径 (CoM(inner)が原点にある前提)
double calculate_semi_major_axis_outer(const Particle& p_outer, const Particle& p_inner1, const Particle& p_inner2, double G);

#endif // ORBITAL_ELEMENTS_H
