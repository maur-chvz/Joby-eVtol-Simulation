#include <gtest/gtest.h>
#include "VehicleMetric.h"

class VehicleMetricsTest : public ::testing::Test {
protected:
    VehicleMetrics metrics;
};

TEST_F(VehicleMetricsTest, RecordFlightUpdatesMetrics) {
    metrics.recordFlight(1.0, 100.0, 2);
    EXPECT_EQ(metrics.getAvgFlightTime(), 1.0);
    EXPECT_EQ(metrics.getAvgDistance(), 100.0);
    EXPECT_EQ(metrics.getTotalPassengerMiles(), 200.0);
}

TEST_F(VehicleMetricsTest, RecordChargeUpdatesMetrics) {
    metrics.recordCharge(0.5);
    EXPECT_EQ(metrics.getAvgChargeTime(), 0.5);
}

TEST_F(VehicleMetricsTest, RecordFaultIncrementsCounter) {
    metrics.recordFault();
    EXPECT_EQ(metrics.getTotalFaults(), 1);
}

TEST_F(VehicleMetricsTest, ZeroCountsReturnZeroAverages) {
    EXPECT_EQ(metrics.getAvgFlightTime(), 0.0);
    EXPECT_EQ(metrics.getAvgDistance(), 0.0);
    EXPECT_EQ(metrics.getAvgChargeTime(), 0.0);
}

TEST_F(VehicleMetricsTest, MultipleRecordsAverageCorrectly) {
    metrics.recordFlight(1.0, 100.0, 2);
    metrics.recordFlight(2.0, 200.0, 2);
    EXPECT_EQ(metrics.getAvgFlightTime(), 1.5);
    EXPECT_EQ(metrics.getAvgDistance(), 150.0);
    EXPECT_EQ(metrics.getTotalPassengerMiles(), 600.0);
}