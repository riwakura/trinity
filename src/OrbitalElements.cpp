#include "OrbitalElements.h"

double calculate_semi_major_axis_inner(const Particle& p1, const Particle& p2, double G) {
    if (p1.m <= 0 || p2.m <= 0) return std::numeric_limits<double>::quiet_NaN(); // 不正な質量

    Vec3D r_rel = p2.r - p1.r;
    Vec3D v_rel = p2.v - p1.v;
    double M_inner = p1.m + p2.m;
    
    double r_mag = r_rel.magnitude();
    // 非常に小さい距離は衝突または数値的不安定とみなす
    if (r_mag < 1e-9) return 0.0; 
    
    double v_sq = v_rel.magnitude_sq();
    double specific_energy = 0.5 * v_sq - G * M_inner / r_mag;

    // エネルギーがほぼゼロまたは正の場合は非束縛
    if (specific_energy >= -1e-12) return std::numeric_limits<double>::infinity(); 
    return -G * M_inner / (2.0 * specific_energy);
}

double calculate_semi_major_axis_outer(const Particle& p_outer, const Particle& p_inner1, const Particle& p_inner2, double G) {
    if (p_outer.m <= 0 || p_inner1.m <= 0 || p_inner2.m <= 0) return std::numeric_limits<double>::quiet_NaN();

    Vec3D r_out_rel = p_outer.r; // CoM(inner)が原点なので、p_outerの位置ベクトルそのもの
    Vec3D v_out_rel = p_outer.v;
    double M_inner = p_inner1.m + p_inner2.m;
    double M_total_system = M_inner + p_outer.m;

    double r_mag = r_out_rel.magnitude();
    if (r_mag < 1e-9) return 0.0; 
    
    double v_sq = v_out_rel.magnitude_sq();
    double specific_energy = 0.5 * v_sq - G * M_total_system / r_mag;
    
    if (specific_energy >= -1e-12) return std::numeric_limits<double>::infinity(); 
    return -G * M_total_system / (2.0 * specific_energy);
}
