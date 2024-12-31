#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <cstdlib>
#include "json.hpp"
#include "Solver.h"
#include "SimulationEngine.h"
#include "SIRModel.h"
#include "SEIRModel.h"

using json = nlohmann::json;

// Function to load parameters from a JSON configuration file
json loadConfig(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open configuration file: " + filename);
    }
    json config;
    file >> config;
    return config;
}

// Function for interactive input
void getInteractiveInput(std::string& model, double& beta, double& gamma, double& sigma, 
                         double& S0, double& I0, double& R0, double& dt, int& steps) {
    std::cout << "Choose a model (SIR/SEIR): ";
    std::cin >> model;

    std::cout << "Enter infection rate (beta): ";
    std::cin >> beta;

    std::cout << "Enter recovery rate (gamma): ";
    std::cin >> gamma;

    if (model == "SEIR") {
        std::cout << "Enter progression rate (sigma): ";
        std::cin >> sigma;
    }

    std::cout << "Enter initial susceptible fraction (S0): ";
    std::cin >> S0;

    std::cout << "Enter initial infected fraction (I0): ";
    std::cin >> I0;

    std::cout << "Enter initial recovered fraction (R0): ";
    std::cin >> R0;

    std::cout << "Enter time step (dt): ";
    std::cin >> dt;

    std::cout << "Enter number of simulation steps: ";
    std::cin >> steps;
}

// Main function
int main(int argc, char* argv[]) {
    // Default values
    std::string model = "SIR";
    double beta = 0.3, gamma = 0.1, sigma = 0.0, S0 = 0.99, I0 = 0.01, R0 = 0.0, dt = 0.01;
    int steps = 100;
    std::string configFile;
    bool useConfig = false;

    // Parse command-line arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--config" && i + 1 < argc) {
            configFile = argv[++i];
            useConfig = true;
        } else if (arg == "--model" && i + 1 < argc) model = argv[++i];
        else if (arg == "--beta" && i + 1 < argc) beta = std::atof(argv[++i]);
        else if (arg == "--gamma" && i + 1 < argc) gamma = std::atof(argv[++i]);
        else if (arg == "--sigma" && i + 1 < argc) sigma = std::atof(argv[++i]);
        else if (arg == "--S0" && i + 1 < argc) S0 = std::atof(argv[++i]);
        else if (arg == "--I0" && i + 1 < argc) I0 = std::atof(argv[++i]);
        else if (arg == "--R0" && i + 1 < argc) R0 = std::atof(argv[++i]);
        else if (arg == "--dt" && i + 1 < argc) dt = std::atof(argv[++i]);
        else if (arg == "--steps" && i + 1 < argc) steps = std::atoi(argv[++i]);
        else {
            std::cerr << "Unknown argument: " << arg << std::endl;
            return 1;
        }
    }

    // Load configuration file if specified and no command-line flags override
    if (useConfig) {
        try {
            json config = loadConfig(configFile);
            model = config.value("model", model);
            beta = config.value("beta", beta);
            gamma = config.value("gamma", gamma);
            sigma = config.value("sigma", sigma);
            S0 = config.value("S0", S0);
            I0 = config.value("I0", I0);
            R0 = config.value("R0", R0);
            dt = config.value("dt", dt);
            steps = config.value("steps", steps);
        } catch (const std::exception& e) {
            std::cerr << "Error loading configuration: " << e.what() << std::endl;
            return 1;
        }
    } else if (argc == 1) {
        // Interactive mode if no command-line arguments or configuration file
        getInteractiveInput(model, beta, gamma, sigma, S0, I0, R0, dt, steps);
    }

    // Create the appropriate model
    std::unique_ptr<Model> simulationModel;
    auto solver = std::make_unique<RK4Solver>();
    if (model == "SIR") {
        simulationModel = std::make_unique<SIRModel>(beta, gamma, std::move(solver));
    } else if (model == "SEIR") {
        simulationModel = std::make_unique<SEIRModel>(beta, gamma, sigma, std::move(solver));
    } else {
        std::cerr << "Invalid model specified." << std::endl;
        return 1;
    }

    // Run the simulation
    SimulationEngine engine(std::move(simulationModel), dt, steps, "simulation_results.csv");
    engine.run(S0, I0, R0);

    return 0;
}
