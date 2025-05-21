#include "IAS15Integrator.h"

IAS15Integrator::IAS15Integrator(OdeFunction ode, void* user_data)
    : ode_func_(ode), user_data_for_ode_(user_data) {
    std::cout << "IAS15Integrator (Stub) Initialized." << std::endl;
}

void IAS15Integrator::set_tolerances(double tol) {
    std::cout << "IAS15Integrator (Stub): Tolerances set to " << tol << std::endl;
    // 本物のIAS15では、内部の許容誤差パラメータを設定します
}

void IAS15Integrator::set_initial_dt(double dt) {
    std::cout << "IAS15Integrator (Stub): Initial dt set to " << dt << std::endl;
    // 本物のIAS15では、最初のステップサイズ候補として利用したりします
}

double IAS15Integrator::get_min_dt() const {
    return current_min_dt_;
}

bool IAS15Integrator::step(std::vector<Particle>& particles, double& t, double& dt) {
    // --- これは実際のIAS15積分ステップのスタブ(仮実装)です ---
    // 実際のIAS15は、以下の複雑なロジックを含みます:
    // - 中間ステージで ode_func_ を複数回呼び出す
    // - 予測子ステップと修正子ステップの計算
    // - 誤差評価
    // - 誤差と許容誤差に基づいて dt を調整
    // - 高精度に粒子の位置と速度を更新

    // このスタブでは、ODE関数を1回呼び出して加速度を取得し、
    // 簡単なオイラー法でデモンストレーションのために更新します。
    if (ode_func_) { // ode_func_が設定されているか確認
        ode_func_(t, particles, user_data_for_ode_);
    }

    for (auto& p : particles) {
        // 簡単なオイラー法による更新 (非常に不正確、単なるプレースホルダー)
        p.v = p.v + p.a * dt;         // 速度更新
        p.r = p.r + p.v * dt;         // 位置更新 (更新された速度を使用)
    }
    t += dt; // 時間を更新

    // std::cout << "IAS15Integrator (Stub): Step taken. t = " << t << ", dt = " << dt << std::endl;
    // 実際の積分器では、ここで次のステップのために dt が変更される可能性があります。
    return true; // スタブは常に「成功」したとします
}
