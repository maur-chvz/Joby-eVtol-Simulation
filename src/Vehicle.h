#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>
#include <random>

#include "VehicleMetric.h"
#include "config.h"

/**
* @brief Current Vehicle State
*/
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
 * 
 * name
 * cruise_speed      (mph)
 * battery_capacity  (kWh)
 * charge_time       (h)
 * cruise_energy_use (kWh/mile)
 * passenger_count   (unit)
 * fault_probability (%/h)
 * 
 * id: unique vehicle identifier
 * state: FLYING, WAITING, or CHARGING
 * start_time: time current flight starts 
 * metrics: simulated metrics captured
 * 
 * max_flight_time (h)
 * max_distance (miles)
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
    double start_time = 0.0;
    VehicleMetrics metrics;

    const double max_flight_time;
    const double max_distance;

public:
    Vehicle(const VehicleConfig& config, int vehicle_id);

    /**
     * @brief Verifies vehicle has not faulted or run out of battery if flying
     *
     * @param [in] current_time time to flight state is simulated
     * @param [in] rng random number generator
     * 
     * @return bool true is flight finished by fault or out of battery
     */
    bool update(double current_time, std::mt19937& rng);

    /**
     * @brief Sets Vehicle state to CHARGING
     */
    void startCharging();

    /**
     * @brief Ends Charging and start Flying
     *
     * @param [in] current_time time Charge finished
     */
    void endCharging(double current_time);

    /**
     * @brief Verifies if Charging was complete
     *
     * @param [in] current_time time when state is checked
     * 
     * @return bool true if enought time to charge has elapsed
     */
    bool isChargingComplete(double current_time) const;

    /**
     * @brief Sets Vehicle state to FLYING
     *
     * @param [in] current_time time flight started
     */
    void startFlying(double current_time);

    /**
     * @brief Returns Vehicle current State
     *
     * @return State holding either FLYING, WAITING, or CHARGING
     */
    State getState() const;

    /**
     * @brief Returns vehicle id
     *
     * @return int id
     */
    int getId() const;

    /**
     * @brief Returns name
     *
     * @return string name
     */
    const std::string& getName() const;

    /**
     * @brief Returns max_flight_time
     *
     * @return double maximum time Vehicle can flight before running out of battery
     */
    const double& getMaxFlightTime() const;

    /**
     * @brief Returns recorded metrics
     *
     * @return Object holding simulation metrics
     */
    const VehicleMetrics& getMetrics() const;
private:
    /**
     * @brief Flight Ends by Running out of fuel or because of Fault
     *
     * @param [in] current_time time at which the flight ended
     */
    void finishFlight(double current_time);

    /**
     * @brief Simulates a random vehicle fault based on exponential failure probability.
     *
     * @param rng A random number generator engine (e.g., std::mt19937).
     * @return true if a fault occurred during the flight, false otherwise.
     */
    bool fault(std::mt19937& rng);
};

#endif