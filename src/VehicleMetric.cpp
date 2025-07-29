#include "VehicleMetric.h"

void VehicleMetrics::recordFlight(double flight_time, double distance, int passengers) {
    ++flight_count;
    total_flight_time += flight_time;
    total_distance += distance;
    total_passenger_miles += distance * passengers;
}

void VehicleMetrics::recordCharge(double charge_time) {
    ++charge_count;
    total_charge_time += charge_time;
}

void VehicleMetrics::recordFault() {
    ++total_faults;
}

double VehicleMetrics::getAvgFlightTime() const {
    return flight_count > 0 ? total_flight_time / flight_count : 0.0;
}

double VehicleMetrics::getAvgDistance() const {
    return flight_count > 0 ? total_distance / flight_count : 0.0;
}

double VehicleMetrics::getAvgChargeTime() const {
    return charge_count > 0 ? total_charge_time / charge_count : 0.0;
}

int VehicleMetrics::getTotalFaults() const { 
    return total_faults; 
}

double VehicleMetrics::getTotalPassengerMiles() const { 
    return total_passenger_miles;
}