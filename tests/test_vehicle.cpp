#include <gtest/gtest.h>
#include "Vehicle.h"
#include "VehicleMetric.h"
#include <random>

class VehicleTest : public ::testing::Test {
protected:
    VehicleConfig config{
        .n = "Test",
        .speed = 100,
        .battery_cap = 100,
        .charge_t = 0.5,
        .energy_use = 1.0,
        .passengers = 2,
        .fault_prob = 0.1
    };
    Vehicle vehicle{config, 1};
    std::mt19937 rng{std::random_device{}()};
};

TEST_F(VehicleTest, ConstructorSetsCorrectValues) {
    EXPECT_EQ(vehicle.getName(), "Test");
    EXPECT_EQ(vehicle.getId(), 1);
    EXPECT_EQ(vehicle.getState(), State::FLYING);
}

TEST_F(VehicleTest, StartChargingSetsState) {
    vehicle.startCharging();
    EXPECT_EQ(vehicle.getState(), State::CHARGING);
}

TEST_F(VehicleTest, EndChargingRestoresBatteryAndStartsFlying) {
    vehicle.startCharging();
    vehicle.endCharging(1.0);
    EXPECT_EQ(vehicle.getState(), State::FLYING);
}

TEST_F(VehicleTest, IsChargingComplete) {
    vehicle.startCharging();
    EXPECT_FALSE(vehicle.isChargingComplete(0.2));
    EXPECT_TRUE(vehicle.isChargingComplete(0.6));
}

TEST_F(VehicleTest, UpdateWhileFlyingNoFault) {
    vehicle.startFlying(0.0);
    std::mt19937 no_fault_rng(1);
    EXPECT_FALSE(vehicle.update(0.1, no_fault_rng));
}

TEST_F(VehicleTest, UpdateWithMaxFlightTime) {
    vehicle.startFlying(0.0);
    double max_time = vehicle.getMaxFlightTime();
    EXPECT_TRUE(vehicle.update(max_time, rng));
    EXPECT_EQ(vehicle.getState(), State::WAITING);
    const auto& metrics = vehicle.getMetrics();
    EXPECT_DOUBLE_EQ(metrics.getAvgFlightTime(), 1.0);
    EXPECT_DOUBLE_EQ(metrics.getAvgDistance(), 100.0);
    EXPECT_DOUBLE_EQ(metrics.getTotalPassengerMiles(), 200.0);
}

TEST_F(VehicleTest, FinishFlightUpdatesMetrics) {

    VehicleConfig test_config{
        .n = "Test",
        .speed = 100.0,
        .battery_cap = 100.0,
        .charge_t = 0.5,
        .energy_use = 1.0,
        .passengers = 2,
        .fault_prob = 5.0e6
    };

    Vehicle test_vehicle{test_config, 1};
    test_vehicle.startFlying(0.0);
    std::mt19937 fault_rng(1);
    
    EXPECT_TRUE(test_vehicle.update(1.0, fault_rng));
    EXPECT_EQ(test_vehicle.getState(), State::WAITING);
    const auto& metrics = test_vehicle.getMetrics();
    EXPECT_DOUBLE_EQ(metrics.getAvgFlightTime(), 1.0);
    EXPECT_DOUBLE_EQ(metrics.getAvgDistance(), 100.0);
    EXPECT_DOUBLE_EQ(metrics.getTotalPassengerMiles(), 200.0);
    EXPECT_EQ(metrics.getTotalFaults(), 1);
}