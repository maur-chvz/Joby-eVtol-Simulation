#include "Simulator.h"

Simulator::Simulator() {
    makeConfigurations();
    makeVehicles();
}

void Simulator::makeConfigurations() {
    configurations_.emplace_back(VehicleConfig{
        .n = "Alpha Company",
        .speed = 120,
        .battery_cap = 320,
        .charge_t = 0.6,
        .energy_use = 1.6,
        .passengers = 4,
        .fault_prob = 0.25
    });

    configurations_.emplace_back(VehicleConfig{
        .n = "Bravo Company",
        .speed = 100,
        .battery_cap = 100,
        .charge_t = 0.2,
        .energy_use = 1.5,
        .passengers = 5,
        .fault_prob = 0.10
    });

    configurations_.emplace_back(VehicleConfig{
        .n = "Charlie Company",
        .speed = 160,
        .battery_cap = 220,
        .charge_t = 0.8,
        .energy_use = 2.2,
        .passengers = 3,
        .fault_prob = 0.05
    });

    configurations_.emplace_back(VehicleConfig{
        .n = "Delta Company",
        .speed = 90,
        .battery_cap = 120,
        .charge_t = 0.62,
        .energy_use = 0.8,
        .passengers = 2,
        .fault_prob = 0.22
    });

    configurations_.emplace_back(VehicleConfig{
        .n = "Echo Company",
        .speed = 30,
        .battery_cap = 150,
        .charge_t = 0.3,
        .energy_use = 5.8,
        .passengers = 2,
        .fault_prob = 0.61
    });
}

void Simulator::makeVehicles() {
    
}