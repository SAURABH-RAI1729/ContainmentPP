#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <functional>
#include <fstream>

// Abstract base class for all models
class Model {
public:
    // Initialize the model with population fractions (S0, I0, R0, E0 optional)
    virtual void initialize(double S0, double I0, double R0, double E0 = 0.0) = 0;

    // Perform one step of the simulation
    virtual void step(double dt) = 0;

    // Log the results for the current step
    virtual void logResults(int step, std::ofstream& outputFile) = 0;

    virtual ~Model() = default; // Virtual destructor for proper cleanup
};

#endif // MODEL_H
