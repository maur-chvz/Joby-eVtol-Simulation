#include "Vehicle.h"

Vehicle::Vehicle(const VehicleConfig& config, int vehicle_id)
: name(config.n),
  cruise_speed(config.speed),
  battery_capacity(config.battery_cap),
  charge_time(config.charge_t),
  cruise_energy_use(config.energy_use),
  passenger_count(config.passengers),
  fault_probability(config.fault_prob),
  id(vehicle_id),
  max_flight_time(battery_capacity / (cruise_speed * cruise_energy_use)),
  max_distance(cruise_speed * max_flight_time) {}


bool Vehicle::update(double current_time, std::mt19937& rng) {
    if (state == State::FLYING) {
        double flight_duration = current_time - start_time;
        
        if (fault(flight_duration, rng)) {
            finishFlight(current_time);
            metrics.recordFault();
            return true;
        }
        
        if (flight_duration >= max_flight_time) {
            finishFlight(current_time);
            return true;
        }
    }
    return false;
}

void Vehicle::startCharging(double current_time) {
    state = State::CHARGING;
    start_time = current_time;
}

void Vehicle::endCharging(double current_time) {
    if (state == State::CHARGING) {
        double charge_duration = current_time - start_time;
        metrics.recordCharge(charge_duration);
        current_battery = battery_capacity;
        startFlying(current_time);
    }
}

bool Vehicle::isChargingComplete(double current_time) const {
    return state == State::CHARGING && (current_time - start_time) >= charge_time;
}

void Vehicle::startFlying(double current_time) {
    state = State::FLYING;
    start_time = current_time;
}

State Vehicle::getState() const {
    return state; 
}

int Vehicle::getId() const { 
    return id; 
}

const std::string& Vehicle::getName() const { 
    return name; 
}

const VehicleMetrics& Vehicle::getMetrics() const { 
    return metrics; 
}

void Vehicle::finishFlight(double current_time) {
    double flight_duration = current_time - start_time;
    double distance = std::min(flight_duration * cruise_speed, max_distance);
    
    metrics.recordFlight(flight_duration, distance, passenger_count);
    current_battery = 0.0;
    state = State::WAITING;
}

bool Vehicle::fault(double flight_duration, std::mt19937& rng) {
    static std::exponential_distribution<double> fault_dist;
    double fault_rate = fault_probability;
    
    if (fault_rate <= 0.0) return false;
    
    double fault_probability = 1.0 - std::exp(-fault_rate * flight_duration);
    std::uniform_real_distribution<double> uniform(0.0, 1.0);
    
    return uniform(rng) < fault_probability;
}