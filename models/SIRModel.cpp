#include "SIRModel.h"

SIRModel::SIRModel(double b, double g, std::unique_ptr<Solver> sol)
    : beta(b), gamma(g), solver(std::move(sol)) {
    equations = {
        [this](double, const std::vector<double>& state) { return -beta * state[0] * state[1]; }, // dS/dt
        [this](double, const std::vector<double>& state) { return beta * state[0] * state[1] - gamma * state[1]; }, // dI/dt
        [this](double, const std::vector<double>& state) { return gamma * state[1]; } // dR/dt
    };
}

void SIRModel::initialize(double S0, double I0, double R0, double) {
    S = S0;
    I = I0;
    R = R0;
}

void SIRModel::step(double dt) {
    std::vector<double> state = {S, I, R};
    solver->solve(equations, state, dt);
    S = state[0];
    I = state[1];
    R = state[2];
}

void SIRModel::logResults(int step, std::ofstream& outputFile) {
    outputFile << step << "," << S << "," << I << "," << R << "\n";
}
