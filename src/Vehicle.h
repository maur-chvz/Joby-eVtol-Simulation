#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>
#include <random>

#include "VehicleMetric.h"

enum class State {
    FLYING,
    WAITING,
    CHARGING
};


/**
 * @brief Configuration for vehicle type.
 * 
 * Encapsulating characteristics of a vehicle for more
 * descriptive construction.
 * 
 * Vehicle name
 * Cruise speed         (mph)
 * Battery Capacity     (kWh)
 * Time to Charge       (h)
 * Energy use at Cruise (kWh/mile)
 * Passenger Count 
 * Probability of fault
 * 
 */
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
 * Using VehicleConfig to setup configuration
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

    const double max_flight_time;
    const double max_distance;

public:
    Vehicle(const VehicleConfig& config, int vehicle_id);

    bool update(double current_time, std::mt19937& rng);
    void startCharging(double current_time);
    void endCharging(double current_time);
    bool isChargingComplete(double current_time) const;
    void startFlying(double current_time);

    State getState() const;
    int getId() const;
    const std::string& getName() const;
    const VehicleMetrics& getMetrics() const;
private:
    void finishFlight(double current_time);
    bool fault(double flight_duration, std::mt19937& rng);
};

#endif