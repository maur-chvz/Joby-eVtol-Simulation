#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>

#include "VehicleMetric.h"

enum class State {
    FLYING,
    WAITING,
    CHARGING
};

struct VehicleConfig {
    const std::string n;
    const double speed = 0.0;
    const double battery_cap = 0.0;
    const double charge_t = 0.0;
    const double energy_use = 0.0;
    const int passengers = 0;
    const double fault_prob = 0.0;
};

/**
 * @brief Vehicle Object
 * 
 * Object representing a single vehicle.
 * name : 
 */
class Vehicle {
private:
    const std::string name;
    const double cruise_speed;
    const double battery_capacity;
    const double charge_time;
    const double cruise_energy_use;
    const int passenger_count;
    const double fault_probability;

    const int id;
    State state;
    double current_battery = 0.0;
    double start_time = 0.0;
    VehicleMetrics metrics;

public:
    Vehicle(const VehicleConfig& config, int vehicle_id);
};

#endif