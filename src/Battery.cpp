#include "Battery.h"

void Battery::pushVehicle(Vehicle* Vehicle) {
    queue_.push(Vehicle);
    tryCharging();
}

bool Battery::update(double current_time) {
    if (current_ && current_->isChargingComplete(current_time)) {
        current_->endCharging(current_time);
        current_ = nullptr;
        tryCharging();
        return true;
    }
    return false;
}

bool Battery::isAvailable() const {
    return current_ == nullptr;
}
    
size_t Battery::getQueueSize() const {
    return queue_.size();
}

void Battery::tryCharging() {
    if (current_ == nullptr && !queue_.empty()) {
        current_= queue_.front();
        queue_.pop();
        current_->startCharging(0.0);
    }
}