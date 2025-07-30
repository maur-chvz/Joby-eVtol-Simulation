#ifndef CONFIG_H
#define CONFIG_H

/**
 * @brief Simulation configurations
 * 
 * TIME_STEP: simulation time step (h)
 * DURATION: simulation total time (h)
 * CHARGERS: total number of chargers
 * VEHICLES: total number of vehicles
 * COMPANY_CONFIGURATIONS: total number company types
 */
namespace Config {
    static constexpr double TIME_STEP = 1.0 / 3600;
    static constexpr double DURATION = 3.0;
    static constexpr int CHARGERS = 3;
    static constexpr int VEHICLES = 20;
    static constexpr int COMPANY_CONFIGURATIONS = 5;
}

#endif