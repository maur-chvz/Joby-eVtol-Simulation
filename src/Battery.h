#ifndef BATTERY_H
#define BATTERY_H

#include <queue>

#include "Vehicle.h"

/**
 * @brief Battery Charger object
 * 
 * Object representing a single charging unit
 * 
 * queue_ : queue for FIFO service
 * current_ : pointer to Vehicle currently charging
 */
class Battery {
private:
    std::queue<Vehicle*> queue_;
    Vehicle* current_ = nullptr;

public:

    /**
     * @brief Adds vehicle to queue
     * 
     * @param [in] vehicle pointer to vehicle
     */
    void pushVehicle(Vehicle* vehicle); // TO DO: check id to avoid repeats?

    /**
     * @brief Returs whether charging Vehicle has finished charging
     * 
     * @return bool true if current charging Vehicle has finised charging
     */
    bool update(double current_time);

    /**
     * @brief Returns availability of current charging unit
     * 
     * @return bool true if no Vehicle is currently being charged
     */
    bool isAvailable() const;

    /**
     * @brief Returs current number of Vehicles in queue
     * 
     * @return size_t elements still in queue
     */
    size_t getQueueSize() const;

    /**
     * @brief If no other vehicle is being charged, and there
     * are vehicles in the queue, starts charging next
     */
    void tryCharging();
};

#endif