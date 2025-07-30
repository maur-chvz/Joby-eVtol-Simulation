#include <gtest/gtest.h>

#include <memory>

#include "Battery.h"
#include "Vehicle.h"

class BatteryTest : public ::testing::Test {
protected:
    void SetUp() override {
        battery = std::make_unique<Battery>();
    }

    void TearDown() override {
        battery.reset();
    }

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

    std::unique_ptr<Battery> battery;
};

TEST_F(BatteryTest, InitialState) {
    EXPECT_TRUE(battery->isAvailable());
    EXPECT_EQ(battery->getQueueSize(), 0);
}

TEST_F(BatteryTest, PushSingleVehicle) {
    battery->pushVehicle(&vehicle);
    
    EXPECT_FALSE(battery->isAvailable());
    EXPECT_EQ(battery->getQueueSize(), 0);
}

TEST_F(BatteryTest, PushMultipleVehicles) {
    battery->pushVehicle(&vehicle);
    battery->pushVehicle(&vehicle);
    battery->pushVehicle(&vehicle);
    
    EXPECT_FALSE(battery->isAvailable());
    EXPECT_EQ(battery->getQueueSize(), 2);
}

TEST_F(BatteryTest, UpdateWithNoVehicleReturnsFalse) {
    EXPECT_FALSE(battery->update(1.0));
}

TEST_F(BatteryTest, UpdateWithVehicleChargeIncomplete) {
    battery->pushVehicle(&vehicle);
    vehicle.startFlying(0.0);

    EXPECT_FALSE(battery->update(1.0));
}

TEST_F(BatteryTest, UpdateWithVehicleChargeComplete) {
    battery->pushVehicle(&vehicle);

    EXPECT_TRUE(battery->update(1.0));
}

TEST_F(BatteryTest, TryChargingWithEmptyQueueDoesNothing) {
    battery->tryCharging();
    EXPECT_TRUE(battery->isAvailable());
    EXPECT_EQ(battery->getQueueSize(), 0);
}

TEST_F(BatteryTest, TryChargingWithQueueAndNoCurrent) {
    battery->pushVehicle(&vehicle);
    battery->tryCharging();
    EXPECT_FALSE(battery->isAvailable());
    EXPECT_EQ(battery->getQueueSize(), 0);
}