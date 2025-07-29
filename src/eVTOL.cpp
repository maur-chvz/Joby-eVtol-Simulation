#include <iostream>

#include "Vehicle.h"

int main() {

    VehicleConfig config1{.n = "Alpha",
                          .speed = 120,
                          .battery_cap = 320,
                          .charge_t = 0.6,
                          .energy_use = 1.6,
                          .passengers = 4,
                          .fault_prob = 0.25
                        };

    Vehicle vehicle1(config1, 1);
    return 0;
}