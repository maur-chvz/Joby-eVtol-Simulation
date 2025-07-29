#include <iostream>

#include "Simulator.h"

int main() {
    try {
        std::cout << "Starting eVTOL Simulation...\n";
        std::cout << "Simulation parameters:\n";
        std::cout << "- Duration: 3 hours\n";
        std::cout << "- Total vehicles: 20\n";
        std::cout << "- Available chargers: 3\n";
        std::cout << "- Time step: 10ms\n\n";
        
        Simulator sim;
        sim.run();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}