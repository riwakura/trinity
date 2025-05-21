#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vec3D.h"

struct Particle {
    double m = 0.0; // 質量
    Vec3D r;        // 位置 (CoM(inner)座標系)
    Vec3D v;        // 速度 (CoM(inner)座標系)
    Vec3D a;        // 加速度 (CoM(inner)座標系, ODE関数が計算)

    Particle();
    Particle(double mass, Vec3D pos, Vec3D vel);
};

#endif // PARTICLE_H
