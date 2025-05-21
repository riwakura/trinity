#ifndef IAS15_INTEGRATOR_H
#define IAS15_INTEGRATOR_H

#include <vector>
#include <functional>
#include <iostream>     // スタブのメッセージ用
#include "Particle.h"   // Particle の定義が必要
#include "OdeFunctions.h" // OdeFunction の型定義が必要

class IAS15Integrator {
public:
    double current_min_dt_ = 1e-16; // 許容される最小時間刻み (例)

    IAS15Integrator(OdeFunction ode, void* user_data);

    void set_tolerances(double tol);
    void set_initial_dt(double dt); // IAS15では内部で決定することが多いが、スタブ用
    double get_min_dt() const;

    // 時間積分を1ステップ進める
    bool step(std::vector<Particle>& particles, double& t, double& dt);

private:
    OdeFunction ode_func_;
    void* user_data_for_ode_;
    // IAS15 の実際の内部状態 (係数配列など) はここにメンバとして保持
    // struct IAS15InternalData internal_data_; // (将来的に)
};

#endif // IAS15_INTEGRATOR_H
