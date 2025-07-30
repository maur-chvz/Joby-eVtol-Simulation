#include <gtest/gtest.h>

#include <random>

#include "Vehicle.h"
#include "Simulator.h"
#include "config.h"

class SimulatorTest : public ::testing::Test {
protected:
    Simulator simulator;
};

TEST_F(SimulatorTest, MakeConfigurationsCreatesCorrectNumber) {
    EXPECT_EQ(simulator.getConfigurations().size(), Config::COMPANY_CONFIGURATIONS);
}

TEST_F(SimulatorTest, MakeVehiclesCreatesCorrectNumber) {
    EXPECT_EQ(simulator.getVehicles().size(), Config::VEHICLES);
}

TEST_F(SimulatorTest, ConfigurationsHaveCorrectValues) {
    const auto& configs = simulator.getConfigurations();
    EXPECT_EQ(configs[0].n, "Alpha Company");
    EXPECT_EQ(configs[1].n, "Bravo Company");
    EXPECT_EQ(configs[2].n, "Charlie Company");
    EXPECT_EQ(configs[3].n, "Delta Company");
    EXPECT_EQ(configs[4].n, "Echo Company");
}

TEST_F(SimulatorTest, AssignChargerIsTriggeredWhenVehicleFinishesFlight) {
    Simulator sim;

    auto& vehicles = sim.getVehicles();
    ASSERT_FALSE(vehicles.empty());

    Vehicle* test_vehicle = vehicles[0].get();

    std::mt19937 fault_rng(1);
    test_vehicle->endCharging(0.0);
    test_vehicle->update(1.0, fault_rng);

    sim.run();

    const auto& chargers = sim.getChargers();
    bool vehicle_assigned = std::any_of(chargers.begin(), chargers.end(),
        [&](const Battery& b) {
            return b.getQueueSize() > 0;
        });

    EXPECT_TRUE(vehicle_assigned);
}

TEST_F(SimulatorTest, RunCompletesWithoutErrors) {
    EXPECT_NO_THROW(simulator.run());
}