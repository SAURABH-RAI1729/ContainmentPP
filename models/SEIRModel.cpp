#include "SEIRModel.h"

SEIRModel::SEIRModel(double b, double g, double s, std::unique_ptr<Solver> sol)
    : beta(b), gamma(g), sigma(s), solver(std::move(sol)) {
    equations = {
        [this](double, const std::vector<double>& state) { return -beta * state[0] * state[2]; }, // dS/dt
        [this](double, const std::vector<double>& state) { return beta * state[0] * state[2] - sigma * state[1]; }, // dE/dt
        [this](double, const std::vector<double>& state) { return sigma * state[1] - gamma * state[2]; }, // dI/dt
        [this](double, const std::vector<double>& state) { return gamma * state[2]; } // dR/dt
    };
}

void SEIRModel::initialize(double S0, double E0, double I0, double R0) {
    S = S0;
    E = E0;
    I = I0;
    R = R0;
}

void SEIRModel::step(double dt) {
    std::vector<double> state = {S, E, I, R};
    solver->solve(equations, state, dt);
    S = state[0];
    E = state[1];
    I = state[2];
    R = state[3];
}

void SEIRModel::logResults(int step, std::ofstream& outputFile) {
    outputFile << step << "," << S << "," << E << "," << I << "," << R << "\n";
}
