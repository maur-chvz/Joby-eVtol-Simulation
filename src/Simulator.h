#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include <memory>
#include <random>
#include <chrono>
#include <unordered_map>
#include <iomanip>
#include <algorithm>

#include "Vehicle.h"
#include "Battery.h"
#include "config.h"

/**
 * @brief Simulator object.
 * 
 * Runs a simulation on a static set of configurations
 * 
 * configurations_ : all possible configurations (hard-coded)
 * vehicles_ : all simulation vehicles
 * chargers_ : all available chargers
 * rng_ : random number generation for number of configurations
 */
class Simulator {
private:
    std::vector<VehicleConfig> configurations_;
    std::vector<std::unique_ptr<Vehicle>> vehicles_;
    std::vector<Battery> chargers_;
    std::mt19937 rng_;

public:
    Simulator();

    /**
     * @brief Runs simulation with parameters defined in config.h
     * 
     */
    void run();

    /**
     * @brief Returns constant reference to Congiguration vector
     *
     * @return vector reference to configurations_
     */
    const std::vector<VehicleConfig>& getConfigurations() const;

    /**
     * @brief Returns constant reference to Vehicle vector
     *
     * @return vector reference to vehicle_
     */
    const std::vector<std::unique_ptr<Vehicle>>& getVehicles() const;

    /**
     * @brief Returns constant reference to Chargers vector
     *
     * @return vector reference to chargers_
     */
    const std::vector<Battery>& getChargers() const;

private:
    /**
     * @brief Creates configuration settings for Hard-Coded Company types
     */
    void makeConfigurations();

    /**
     * @brief Makes a random number of vehicles for each configuration
     */
    void makeVehicles();

    /**
     * @brief Assigns the most optimal charger at current time
     *
     * @param [in] vehicle pointer to vehicle object
     */
    void assignCharger(Vehicle* vehicle);

    /**
     * @brief Prints metrics collected in simulation
     */
    void printResults() const;
};

#endif