#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

enum class State {
    FLYING,
    WAITING,
    CHARGING
};

class Vehicle {
private:
    const std::string name;
    const double cruise_speed;
    const double battery_capacity;
    const double charge_time;
    const double cruise_energy_use;
    const int passenger_count;
    const double fault_probability;
public:
    Vehicle(const std::string& n, double speed, double battery, double charge, double cruise_energy, int passengers, double fault);
};

#endif