#include "Simulator.h"

Simulator::Simulator() : chargers_(Config::CHARGERS), rng_(std::random_device{}()) {
    makeConfigurations();
    makeVehicles();
}

void Simulator::run() {
    auto start_time = std::chrono::high_resolution_clock::now();
    
    for (double time = 0.0; time <= Config::DURATION; time += Config::TIME_STEP) {
        for (auto& vehicle : vehicles_) {
            State current_state = vehicle->getState();

            if(current_state == State::FLYING) {
                if (vehicle->update(time, rng_)) {
                    assignCharger(vehicle.get());
                }
            }

            else if(current_state == State::WAITING) {
                continue;
            }
        }
        
        for (auto& charger : chargers_) {
            charger.update(time);
        }
    }
    
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    
    std::cout << "Simulation completed in " << duration.count() << " microseconds\n\n";
    printResults();
}

void Simulator::makeConfigurations() {
    configurations_.emplace_back(VehicleConfig{
        .n = "Alpha Company",
        .speed = 120,
        .battery_cap = 320,
        .charge_t = 0.6,
        .energy_use = 1.6,
        .passengers = 4,
        .fault_prob = 0.25
    });

    configurations_.emplace_back(VehicleConfig{
        .n = "Bravo Company",
        .speed = 100,
        .battery_cap = 100,
        .charge_t = 0.2,
        .energy_use = 1.5,
        .passengers = 5,
        .fault_prob = 0.10
    });

    configurations_.emplace_back(VehicleConfig{
        .n = "Charlie Company",
        .speed = 160,
        .battery_cap = 220,
        .charge_t = 0.8,
        .energy_use = 2.2,
        .passengers = 3,
        .fault_prob = 0.05
    });

    configurations_.emplace_back(VehicleConfig{
        .n = "Delta Company",
        .speed = 90,
        .battery_cap = 120,
        .charge_t = 0.62,
        .energy_use = 0.8,
        .passengers = 2,
        .fault_prob = 0.22
    });

    configurations_.emplace_back(VehicleConfig{
        .n = "Echo Company",
        .speed = 30,
        .battery_cap = 150,
        .charge_t = 0.3,
        .energy_use = 5.8,
        .passengers = 2,
        .fault_prob = 0.61
    });
}

void Simulator::makeVehicles() { // TO DO: make random ordere of vehicles
    std::vector<int> vehicle_counts(configurations_.size(), 0);
    std::uniform_int_distribution<int> spec_dist(0, configurations_.size() - 1);
    
    for (int i = 0; i < Config::VEHICLES; ++i) {
        vehicle_counts[spec_dist(rng_)]++;
    }
    
    int vehicle_id = 0;
    for (size_t spec_idx = 0; spec_idx < configurations_.size(); ++spec_idx) {
        for (int i = 0; i < vehicle_counts[spec_idx]; ++i) {
            vehicles_.emplace_back(
                std::make_unique<Vehicle>(configurations_[spec_idx], vehicle_id++)
            );
        }
    }
    
    std::cout << "Vehicle Distribution:\n";
    for (size_t i = 0; i < configurations_.size(); ++i) {
        std::cout << configurations_[i].n << ": " << vehicle_counts[i] << " vehicles\n";
    }
    std::cout << "\n";
}

void Simulator::assignCharger(Vehicle* vehicle) {
    auto best_charger = std::min_element(chargers_.begin(), chargers_.end(),
        [](const Battery& a, const Battery& b) {
            return a.getQueueSize() < b.getQueueSize();
        });
        
    best_charger->pushVehicle(vehicle);
}

void Simulator::printResults() const {
    std::unordered_map<std::string, int> vehicle_counts;
    
    for (const auto& vehicle : vehicles_) {
        const std::string& name = vehicle->getName();
        vehicle_counts[name]++;
    }
    
    std::cout << "=== SIMULATION RESULTS ===\n\n";
    std::cout << std::fixed << std::setprecision(2);
    
    for (const auto& spec : configurations_) {
        std::cout << spec.n << ":\n";
        
        VehicleMetrics combined_stats;
        int count = 0;
        double total_flight_time = 0, total_distance = 0, total_charge_time = 0;
        int total_faults = 0;
        double total_passenger_miles = 0;
        
        for (const auto& vehicle : vehicles_) {
            if (vehicle->getName() == spec.n) {
                const auto& metrics = vehicle->getMetrics();
                total_flight_time += metrics.getAvgFlightTime();
                total_distance += metrics.getAvgDistance();
                total_charge_time += metrics.getAvgChargeTime();
                total_faults += metrics.getTotalFaults();
                total_passenger_miles += metrics.getTotalPassengerMiles();
                count++;
            }
        }
        
        if (count > 0) {
            std::cout << "  Vehicles: " << count << "\n";
            std::cout << "  Average flight time per flight: " 
                        << (total_flight_time / count) << " hours\n";
            std::cout << "  Average distance per flight: " 
                        << (total_distance / count) << " miles\n";
            std::cout << "  Average charging time per session: " 
                        << (total_charge_time / count) << " hours\n";
            std::cout << "  Total faults: " << total_faults << "\n";
            std::cout << "  Total passenger miles: " 
                        << total_passenger_miles << "\n";
        } else {
            std::cout << "  No vehicles of this type\n";
        }
        std::cout << "\n";
    }
}

const std::vector<VehicleConfig>& Simulator::getConfigurations() const {
        return configurations_;
    }
    
const std::vector<std::unique_ptr<Vehicle>>& Simulator::getVehicles() const {
    return vehicles_;
}

const std::vector<Battery>& Simulator::getChargers() const {
    return chargers_;
}
