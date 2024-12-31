#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <functional>

// Solver base class for numerical integration
class Solver {
public:
    // Solve a system of differential equations
    virtual void solve(std::vector<std::function<double(double, const std::vector<double>&)>> equations,
                       std::vector<double>& state, double dt) = 0;

    virtual ~Solver() = default; // Virtual destructor
};

// Implementation of the RK4 solver for high-accuracy integration
class RK4Solver : public Solver {
public:
    void solve(std::vector<std::function<double(double, const std::vector<double>&)>> equations,
               std::vector<double>& state, double dt) override;
};

#endif // SOLVER_H
