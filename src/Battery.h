#ifndef BATTERY_H
#define BATTERY_H

#include <queue>

#include "Vehicle.h"

class Battery {
private:
    std::queue<Vehicle*> queue_;
    Vehicle* current_ = nullptr;

public:
    void pushVehicle(Vehicle* vehicle);
    bool update(double current_time);
    bool isAvailable() const;
    size_t getQueueSize() const;
    void tryCharging();
};

#endif