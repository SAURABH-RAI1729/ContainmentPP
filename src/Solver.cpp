#include "Solver.h"

void RK4Solver::solve(std::vector<std::function<double(double, const std::vector<double>&)>> equations,
                      std::vector<double>& state, double dt) {
    std::vector<double> k1(state.size()), k2(state.size()), k3(state.size()), k4(state.size()), temp(state.size());

    // Compute k1
    for (size_t i = 0; i < state.size(); ++i)
        k1[i] = equations[i](0.0, state);

    // Compute k2
    for (size_t i = 0; i < state.size(); ++i)
        temp[i] = state[i] + 0.5 * dt * k1[i];
    for (size_t i = 0; i < state.size(); ++i)
        k2[i] = equations[i](0.0, temp);

    // Compute k3
    for (size_t i = 0; i < state.size(); ++i)
        temp[i] = state[i] + 0.5 * dt * k2[i];
    for (size_t i = 0; i < state.size(); ++i)
        k3[i] = equations[i](0.0, temp);

    // Compute k4
    for (size_t i = 0; i < state.size(); ++i)
        temp[i] = state[i] + dt * k3[i];
    for (size_t i = 0; i < state.size(); ++i)
        k4[i] = equations[i](0.0, temp);

    // Update the state
    for (size_t i = 0; i < state.size(); ++i)
        state[i] += dt / 6.0 * (k1[i] + 2.0 * k2[i] + 2.0 * k3[i] + k4[i]);
}
