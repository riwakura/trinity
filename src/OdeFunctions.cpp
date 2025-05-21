#include "OdeFunctions.h"
#include <stdexcept> // For std::runtime_error
#include <cmath>     // For std::sqrt (Vec3D内で使用)

void hierarchical_triple_ode(double t, std::vector<Particle>& particles, void* user_data) {
    if (particles.size() != 3) {
        throw std::runtime_error("hierarchical_triple_ode expects 3 particles.");
    }
    double G = *static_cast<double*>(user_data);

    Particle& p1 = particles[0];
    Particle& p2 = particles[1];
    Particle& p3 = particles[2];

    // ゼロ質量チェック
    if (p1.m <= 0 || p2.m <= 0 || p3.m <= 0) {
         throw std::runtime_error("Particle mass must be positive.");
    }

    // --- 力の計算 ---
    Vec3D r12 = p2.r - p1.r; double d12_sq = r12.magnitude_sq(); double d12 = std::sqrt(d12_sq);
    Vec3D r13 = p3.r - p1.r; double d13_sq = r13.magnitude_sq(); double d13 = std::sqrt(d13_sq);
    Vec3D r23 = p3.r - p2.r; double d23_sq = r23.magnitude_sq(); double d23 = std::sqrt(d23_sq);

    // 衝突を避けるための微小距離 (ソフトニングはしないがゼロ除算を避ける)
    const double softening_eps_sq = 1e-12; // 距離の2乗に対する微小値

    Vec3D F12, F13_on1, F21, F23_on2, F31_on3, F32_on3;

    if (d12_sq > softening_eps_sq) F12 = r12 * (G * p1.m * p2.m / (d12_sq * d12)); else F12 = Vec3D();
    F21 = F12 * -1.0;

    if (d13_sq > softening_eps_sq) F13_on1 = r13 * (G * p1.m * p3.m / (d13_sq * d13)); else F13_on1 = Vec3D();
    F31_on3 = F13_on1 * -1.0; // p3 に p1 からかかる力

    if (d23_sq > softening_eps_sq) F23_on2 = r23 * (G * p2.m * p3.m / (d23_sq * d23)); else F23_on2 = Vec3D();
    F32_on3 = F23_on2 * -1.0; // p3 に p2 からかかる力


    // --- CoM(inner)の慣性系に対する加速度 ---
    double M_inner_inv = 1.0 / (p1.m + p2.m);
    Vec3D A_CoM_inner = (F13_on1 + F23_on2) * M_inner_inv; // p1へのF3とp2へのF3によるCoM加速度

    // --- CoM(inner)座標系での加速度 ---
    p1.a = (F12 + F13_on1) / p1.m - A_CoM_inner;
    p2.a = (F21 + F23_on2) / p2.m - A_CoM_inner;
    p3.a = (F31_on3 + F32_on3) / p3.m - A_CoM_inner;
}
