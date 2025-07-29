#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include <memory>

#include "Vehicle.h"

class Simulator {
private:
    static constexpr double TIME_STEP = 0.01;
    static constexpr double DURATION = 3.0;
    static constexpr int CHARGERS = 3;
    static constexpr int VEHICLES = 20;

    std::vector<VehicleConfig> configurations_;
    std::vector<std::unique_ptr<Vehicle>> vehicles_;

public:
    Simulator();

    void makeConfigurations();
    void makeVehicles();
};

#endif