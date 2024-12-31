#include "SimulationEngine.h"
#include <fstream>
#include <iostream>

SimulationEngine::SimulationEngine(std::unique_ptr<Model> m, double timestep, int simSteps, const std::string& outputFile)
    : model(std::move(m)), dt(timestep), steps(simSteps), outputFileName(outputFile) {}

void SimulationEngine::run(double S0, double I0, double R0, double E0) {
    model->initialize(S0, I0, R0, E0);

    std::ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file!\n";
        return;
    }

    outputFile << "Step,S,E,I,R\n";

    for (int t = 0; t < steps; ++t) {
        model->step(dt);
        model->logResults(t, outputFile);
    }

    outputFile.close();
    std::cout << "Simulation completed. Results saved to " << outputFileName << "\n";
}
