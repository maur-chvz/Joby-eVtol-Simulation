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
  state(State::FLYING),
  max_flight_time(battery_capacity / (cruise_speed * cruise_energy_use)),
  max_distance(cruise_speed * max_flight_time) {}


bool Vehicle::update(double current_time, std::mt19937& rng) {
    if (state == State::FLYING) {
        double flight_duration = current_time - start_time;

        if (fault(rng)) {
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

void Vehicle::startCharging() {
    state = State::CHARGING;
}

void Vehicle::endCharging(double current_time) {
    if (state == State::CHARGING) {
        double charge_duration = current_time - start_time;
        metrics.recordCharge(charge_duration);
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

const double& Vehicle::getMaxFlightTime() const {
    return max_flight_time;
}

const VehicleMetrics& Vehicle::getMetrics() const { 
    return metrics; 
}

void Vehicle::finishFlight(double current_time) {
    double flight_duration = current_time - start_time;
    double distance = std::min(flight_duration * cruise_speed, max_distance);
    
    metrics.recordFlight(flight_duration, distance, passenger_count);
    state = State::WAITING;
    start_time = current_time;
}

bool Vehicle::fault(std::mt19937& rng) {
    double fault_rate = fault_probability;
    
    if (fault_rate <= 0.0) return false;
    
    double fault_probability = 1.0 - std::exp(-fault_rate * Config::TIME_STEP);
    std::uniform_real_distribution<double> uniform(0.0, 1.0);
    
    return uniform(rng) < fault_probability;
}