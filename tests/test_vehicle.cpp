#include <gtest/gtest.h>
#include "src/Vehicle.h"

TEST(VehicleTest, InitializesCorrectly) {
    Vehicle v("Alpha", 120, 320, 0.6, 1.6, 4, 0.25);
    EXPECT_EQ(v.getName(), "Alpha");
    EXPECT_EQ(v.getPassengerCount(), 4);
}
