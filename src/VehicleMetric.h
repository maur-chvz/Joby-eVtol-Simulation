#ifndef VEHICLEMETRIC_H
#define VEHICLEMETRIC_H

class VehicleMetrics {
private:
    int flight_count = 0;
    int charge_count = 0;
    double total_flight_time = 0.0;
    double total_distance = 0.0;
    double total_charge_time = 0.0;
    int total_faults = 0;
    double total_passenger_miles = 0.0;
public:
    void recordFlight(double flight_time, double distance, int passengers);
    void recordCharge(double charge_time);
    void recordFault();
    
    double getAvgFlightTime() const;
    double getAvgDistance() const;
    double getAvgChargeTime() const;
    int getTotalFaults() const;
    double getTotalPassengerMiles() const;
};

#endif