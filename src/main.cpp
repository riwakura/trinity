#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>   // For std::fixed, std::setprecision
#include <stdexcept> // For std::runtime_error (もし使うなら)
#include <limits>    // For std::numeric_limits

#include "Vec3D.h"
#include "Particle.h"
#include "OdeFunctions.h"
#include "IAS15Integrator.h"
#include "OrbitalElements.h"

int main() {
    std::cout << std::fixed << std::setprecision(20);

    // --- 1. Constants ---
    const double G_const = 1.0; // N-body units (Heggie units)
    void* ode_user_data = const_cast<double*>(&G_const); // ODE関数にGを渡す

    // --- 2. 粒子の初期化 (CoM(inner)座標系で直接設定) ---
    Particle p1_initial, p2_initial, p3_initial;

    // Inner binary (m1, m2)
    double m1_val = 1.0;
    double m2_val = 1.0;
    double M_inner_val = m1_val + m2_val;
    double a_in_target = 1.0; 

    Vec3D r12_relative_init(a_in_target, 0.0, 0.0);
    p1_initial.m = m1_val;
    p1_initial.r = r12_relative_init * -(m2_val / M_inner_val);
    p2_initial.m = m2_val;
    p2_initial.r = r12_relative_init * (m1_val / M_inner_val);

    double v_orb_in_mag = std::sqrt(G_const * M_inner_val / a_in_target);
    Vec3D v12_relative_init(0.0, v_orb_in_mag, 0.0);
    p1_initial.v = v12_relative_init * -(m2_val / M_inner_val);
    p2_initial.v = v12_relative_init * (m1_val / M_inner_val);

    // Outer body (m3)
    double m3_val = 0.5;
    double a_out_target = 5.0;
    p3_initial.m = m3_val;
    p3_initial.r = Vec3D(a_out_target, 0.0, 0.0); 
    double v_orb_out_mag = std::sqrt(G_const * (M_inner_val + m3_val) / a_out_target);
    p3_initial.v = Vec3D(0.0, v_orb_out_mag, 0.0);

    std::vector<Particle> particles = {p1_initial, p2_initial, p3_initial};

    std::cout << "Initial State (CoM(inner) frame):" << std::endl;
    for (size_t i = 0; i < particles.size(); ++i) {
        std::cout << "P" << i+1 << " (m=" << particles[i].m << "):"
                  << " r=(" << particles[i].r.x << ", " << particles[i].r.y << ", " << particles[i].r.z << ")"
                  << " v=(" << particles[i].v.x << ", " << particles[i].v.y << ", " << particles[i].v.z << ")" << std::endl;
    }

    // --- 3. IAS15積分器のセットアップ (スタブ) ---
    IAS15Integrator integrator(hierarchical_triple_ode, ode_user_data);
    integrator.set_tolerances(1e-9); 
    integrator.set_initial_dt(1e-3); 

    // --- 4. 初期の軌道長半径と比率を計算 ---
    double a_in_initial = calculate_semi_major_axis_inner(particles[0], particles[1], G_const);
    double a_out_initial = calculate_semi_major_axis_outer(particles[2], particles[0], particles[1], G_const);
    
    if (a_out_initial <= 0 || std::isinf(a_out_initial) || std::isnan(a_out_initial) ||
        a_in_initial <= 0 || std::isinf(a_in_initial) || std::isnan(a_in_initial) ) {
        std::cerr << "Error: Initial orbits are unbound or ill-defined." << std::endl;
        std::cerr << "a_in_initial = " << a_in_initial << ", a_out_initial = " << a_out_initial << std::endl;
        return 1;
    }
    double ratio_initial = a_in_initial / a_out_initial;
    std::cout << "Initial: a_in=" << a_in_initial << ", a_out=" << a_out_initial << ", ratio=" << ratio_initial << std::endl;

    // --- 5. 時間積分ループ ---
    double t = 0.0;
    double dt = 1e-3; 
    double t_end = 200.0; 
    int n_steps = 0;
    int output_interval = 10; // 出力/チェック頻度

    while (t < t_end) {
        if (!integrator.step(particles, t, dt)) {
            std::cerr << "Integrator step failed." << std::endl;
            break; 
        }
        n_steps++;

        if (n_steps % output_interval == 0) { 
            double a_in_current = calculate_semi_major_axis_inner(particles[0], particles[1], G_const);
            double a_out_current = calculate_semi_major_axis_outer(particles[2], particles[0], particles[1], G_const);

            if (a_out_current <= 0 || std::isinf(a_out_current) || std::isnan(a_out_current) ||
                a_in_current <= 0 || std::isinf(a_in_current) || std::isnan(a_in_current) ) {
                std::cout << "t = " << t << ": Orbit became unbound or ill-defined." << std::endl;
                break;
            }
            double ratio_current = a_in_current / a_out_current;
            double ratio_change_abs = std::abs((ratio_current - ratio_initial) / ratio_initial);

            std::cout << "t = " << t << ", dt = " << dt
                      << ", a_in = " << a_in_current << ", a_out = " << a_out_current
                      << ", ratio_chg = " << ratio_change_abs * 100.0 << "%"
                      << std::endl;
            
            if (ratio_change_abs >= 0.10) {
                std::cout << "Termination condition met: ratio changed by >=10% at t = " << t << std::endl;
                break;
            }
        }
         if (dt < integrator.get_min_dt() && dt != 0.0){ 
             std::cout << "Time step too small at t = " << t << ", dt = " << dt << std::endl;
             break;
        }
        if (n_steps > 200000 && t_end > 100) { // 安全停止 (スタブのため)
            std::cout << "Reached max steps for stub." << std::endl;
            break;
        }
    }

    std::cout << "Simulation finished after " << n_steps << " steps at t = " << t << std::endl;
    std::cout << "Final State (CoM(inner) frame):" << std::endl;
    for (size_t i = 0; i < particles.size(); ++i) {
        std::cout << "P" << i+1 << " (m=" << particles[i].m << "):"
                  << " r=(" << particles[i].r.x << ", " << particles[i].r.y << ", " << particles[i].r.z << ")"
                  << " v=(" << particles[i].v.x << ", " << particles[i].v.y << ", " << particles[i].v.z << ")" << std::endl;
    }
    return 0;
}
