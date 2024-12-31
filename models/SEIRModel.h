#ifndef SEIRMODEL_H
#define SEIRMODEL_H

#include "Model.h"
#include "Solver.h"
#include <vector>
#include <functional>
#include <memory>

class SEIRModel : public Model {
private:
    double S, E, I, R; // Compartments
    double beta, gamma, sigma; // Parameters
    std::unique_ptr<Solver> solver; // Numerical solver
    std::vector<std::function<double(double, const std::vector<double>&)>> equations;

public:
    SEIRModel(double b, double g, double s, std::unique_ptr<Solver> sol);
    void initialize(double S0, double E0, double I0, double R0) override;
    void step(double dt) override;
    void logResults(int step, std::ofstream& outputFile) override;
};

#endif // SEIRMODEL_H
