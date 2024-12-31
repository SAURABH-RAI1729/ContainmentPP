#ifndef SIMULATIONENGINE_H
#define SIMULATIONENGINE_H

#include <memory>
#include <string>
#include "Model.h"

class SimulationEngine {
private:
    std::unique_ptr<Model> model;
    double dt;
    int steps;
    std::string outputFileName;

public:
    SimulationEngine(std::unique_ptr<Model> m, double timestep, int simSteps, const std::string& outputFile);
    void run(double S0, double I0, double R0, double E0 = 0.0);
};

#endif // SIMULATIONENGINE_H
