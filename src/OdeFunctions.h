#ifndef ODE_FUNCTIONS_H
#define ODE_FUNCTIONS_H

#include <vector>
#include <functional>
#include "Particle.h" // Particle構造体の定義が必要

// ODE関数の型定義
using OdeFunction = std::function<void(double t, std::vector<Particle>& particles, void* user_data)>;

// 階層的三体系のODE関数
void hierarchical_triple_ode(double t, std::vector<Particle>& particles, void* user_data);

#endif // ODE_FUNCTIONS_H
