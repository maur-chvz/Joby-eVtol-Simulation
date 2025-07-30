#ifndef VEHICLEMETRIC_H
#define VEHICLEMETRIC_H

/**
 * @brief Single Vehicle Simulation Metric Object
 * 
 * flight_count          (unit)
 * charge_count          (unit)
 * total_flight_time     (h)
 * total_distance        (miles)
 * total_charge_time     (h)
 * total_faults          (unit)
 * total_passenger_miles (unit)
 */
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

    /**
     * @brief Records when Vehicle completed an entire fly.
     * Records time spent flying, and total distance traveled
     *
     * @param [in] double time spent flying
     * @param [in] double distance traveled in flight
     * @param [in] int number of passangers aboard
     */
    void recordFlight(double flight_time, double distance, int passengers);

    /**
     * @brief Records total time spent charging or waiting
     * for charger, and increases charger counter
     *
     * @param [in] double time spent charging and waiting
     */
    void recordCharge(double charge_time);
    
    /**
     * @brief Records when a fault occured
     */
    void recordFault();
    
    /**
     * @brief Returns average time Vehicle flew
     *
     * @return double total_flight_time / flight_count
     */
    double getAvgFlightTime() const;

    /**
     * @brief Returns average distance traveled by Vehicle
     *
     * @return double total_distance / flight_count
     */
    double getAvgDistance() const;

    /**
     * @brief Returns average time Vehicle stayed charging
     * or waiting for a charger
     *
     * @return double total_passenger_miles / charge_count
     */
    double getAvgChargeTime() const;

    /**
     * @brief Returns total number of faults occured in simulation
     *
     * @return int total_faults
     */
    int getTotalFaults() const;

    /**
     * @brief Returns total PassangerMiles
     *
     * @return double total_passenger_miles
     */
    double getTotalPassengerMiles() const;
};

#endif