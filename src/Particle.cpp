#include "Particle.h"

Particle::Particle() : m(0.0) {} // r, v, a はVec3Dのデフォルトコンストラクタで初期化
Particle::Particle(double mass, Vec3D pos, Vec3D vel) : m(mass), r(pos), v(vel) {}
