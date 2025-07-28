#include "Vehicle.h"

Vehicle::Vehicle(const std::string& n, double speed, double battery, double charge,
                 double cruise_energy, int passengers, double fault)
    : name(n), 
      cruise_speed(speed), 
      battery_capacity(battery), 
      charge_time(charge), 
      cruise_energy_use(cruise_energy), 
      passenger_count(passengers), 
      fault_probability(fault) {}

