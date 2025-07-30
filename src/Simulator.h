#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include <memory>
#include <random>
#include <chrono>
#include <unordered_map>
#include <iomanip>
#include <algorithm>

#include "Vehicle.h"
#include "Battery.h"
#include "config.h"

class Simulator {
private:
    std::vector<VehicleConfig> configurations_;
    std::vector<std::unique_ptr<Vehicle>> vehicles_;
    std::vector<Battery> chargers_;
    std::mt19937 rng_;

public:
    Simulator();
    void run();

private:
    void makeConfigurations();
    void makeVehicles();
    void assignCharger(Vehicle* vehicle);
    void printResults() const;
};

#endif