#ifndef SIRMODEL_H
#define SIRMODEL_H

#include "Model.h"
#include "Solver.h"
#include <vector>
#include <functional>
#include <memory>

class SIRModel : public Model {
private:
    double S, I, R; // Compartments
    double beta, gamma; // Parameters
    std::unique_ptr<Solver> solver; // Numerical solver
    std::vector<std::function<double(double, const std::vector<double>&)>> equations;

public:
    SIRModel(double b, double g, std::unique_ptr<Solver> sol);
    void initialize(double S0, double I0, double R0, double E0 = 0.0) override;
    void step(double dt) override;
    void logResults(int step, std::ofstream& outputFile) override;
};

#endif // SIRMODEL_H
