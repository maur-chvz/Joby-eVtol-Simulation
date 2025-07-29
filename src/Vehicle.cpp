#include "Vehicle.h"

Vehicle::Vehicle(const VehicleConfig& config, int vehicle_id)
: name(config.n),
  cruise_speed(config.speed),
  battery_capacity(config.battery_cap),
  charge_time(config.charge_t),
  cruise_energy_use(config.energy_use),
  passenger_count(config.passengers),
  fault_probability(config.fault_prob),
  id(vehicle_id) {}

