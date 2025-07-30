# eVTOL Simulation Problem

## Overview
This simulation models a fleet of eVTOL vehicles from multiple companies operating with shared charging infrastructure. The system tracks vehicle performance metrics, charging patterns, and operational efficiency across different aircraft configurations.

## Key Assumptions

### Provided Assumptions
- Each vehicle starts with a fully-charged battery
- Vehicles instantaneously reach cruise speed
- Vehicles remain airborne until battery depletion
- Immediate queuing for charging after battery depletion

### Implementation Assumptions
- Faults follow a Poisson distribution process
- Vehicles queue immediately when battery depletes or fault occurs
- Flight continues until battery depletion or fault occurrence
- Charging process runs to completion without interruption


### Default Configuration
- **Simulation Duration**: 3 hours
- **Total Vehicles**: 20
- **Available Chargers**: 3
- **Time Step**: 1 second

## Metrics Tracked
  - Average flight time per flight
  - Average distance per flight
  - Average charging time per session
  - Total fault occurrences
  - Total passenger miles



# Sample Output

```
Starting eVTOL Simulation...
Simulation parameters:
- Duration: 3 hours
- Total vehicles: 20
- Available chargers: 3
- Time step: 1s

Vehicle Distribution:
Alpha Company: 4 vehicles
Bravo Company: 2 vehicles
Charlie Company: 1 vehicles
Delta Company: 8 vehicles
Echo Company: 5 vehicles

Simulation completed in 143136 microseconds

=== SIMULATION RESULTS ===

Alpha Company:
  Vehicles: 4
  Average flight time per flight: 1.15 hours
  Average distance per flight: 137.79 miles
  Average charging time per session: 0.60 hours
  Total faults: 4
  Total passenger miles: 3161.47

Bravo Company:
  Vehicles: 2
  Average flight time per flight: 0.67 hours
  Average distance per flight: 66.67 miles
  Average charging time per session: 0.20 hours
  Total faults: 0
  Total passenger miles: 2000.00

Charlie Company:
  Vehicles: 1
  Average flight time per flight: 0.63 hours
  Average distance per flight: 100.00 miles
  Average charging time per session: 0.80 hours
  Total faults: 0
  Total passenger miles: 600.00

Delta Company:
  Vehicles: 8
  Average flight time per flight: 1.56 hours
  Average distance per flight: 140.55 miles
  Average charging time per session: 0.62 hours
  Total faults: 2
  Total passenger miles: 2459.65

Echo Company:
  Vehicles: 5
  Average flight time per flight: 0.68 hours
  Average distance per flight: 20.50 miles
  Average charging time per session: 0.40 hours
  Total faults: 6
  Total passenger miles: 521.12
```

  # Unit Testing

```
[==========] Running 25 tests from 4 test suites.
[----------] Global test environment set-up.
[----------] 7 tests from VehicleTest
[ RUN      ] VehicleTest.ConstructorSetsCorrectValues
[       OK ] VehicleTest.ConstructorSetsCorrectValues (0 ms)
[ RUN      ] VehicleTest.StartChargingSetsState
[       OK ] VehicleTest.StartChargingSetsState (0 ms)
[ RUN      ] VehicleTest.EndChargingRestoresBatteryAndStartsFlying
[       OK ] VehicleTest.EndChargingRestoresBatteryAndStartsFlying (0 ms)
[ RUN      ] VehicleTest.IsChargingComplete
[       OK ] VehicleTest.IsChargingComplete (0 ms)
[ RUN      ] VehicleTest.UpdateWhileFlyingNoFault
[       OK ] VehicleTest.UpdateWhileFlyingNoFault (54 ms)
[ RUN      ] VehicleTest.UpdateWithMaxFlightTime
[       OK ] VehicleTest.UpdateWithMaxFlightTime (0 ms)
[ RUN      ] VehicleTest.FinishFlightUpdatesMetrics
[       OK ] VehicleTest.FinishFlightUpdatesMetrics (0 ms)
[----------] 7 tests from VehicleTest (56 ms total)

[----------] 5 tests from VehicleMetricsTest
[ RUN      ] VehicleMetricsTest.RecordFlightUpdatesMetrics
[       OK ] VehicleMetricsTest.RecordFlightUpdatesMetrics (0 ms)
[ RUN      ] VehicleMetricsTest.RecordChargeUpdatesMetrics
[       OK ] VehicleMetricsTest.RecordChargeUpdatesMetrics (0 ms)
[ RUN      ] VehicleMetricsTest.RecordFaultIncrementsCounter
[       OK ] VehicleMetricsTest.RecordFaultIncrementsCounter (0 ms)
[ RUN      ] VehicleMetricsTest.ZeroCountsReturnZeroAverages
[       OK ] VehicleMetricsTest.ZeroCountsReturnZeroAverages (0 ms)
[ RUN      ] VehicleMetricsTest.MultipleRecordsAverageCorrectly
[       OK ] VehicleMetricsTest.MultipleRecordsAverageCorrectly (0 ms)
[----------] 5 tests from VehicleMetricsTest (0 ms total)

[----------] 8 tests from BatteryTest
[ RUN      ] BatteryTest.InitialState
[       OK ] BatteryTest.InitialState (0 ms)
[ RUN      ] BatteryTest.PushSingleVehicle
[       OK ] BatteryTest.PushSingleVehicle (0 ms)
[ RUN      ] BatteryTest.PushMultipleVehicles
[       OK ] BatteryTest.PushMultipleVehicles (0 ms)
[ RUN      ] BatteryTest.UpdateWithNoVehicleReturnsFalse
[       OK ] BatteryTest.UpdateWithNoVehicleReturnsFalse (0 ms)
[ RUN      ] BatteryTest.UpdateWithVehicleChargeIncomplete
[       OK ] BatteryTest.UpdateWithVehicleChargeIncomplete (0 ms)
[ RUN      ] BatteryTest.UpdateWithVehicleChargeComplete
[       OK ] BatteryTest.UpdateWithVehicleChargeComplete (0 ms)
[ RUN      ] BatteryTest.TryChargingWithEmptyQueueDoesNothing
[       OK ] BatteryTest.TryChargingWithEmptyQueueDoesNothing (0 ms)
[ RUN      ] BatteryTest.TryChargingWithQueueAndNoCurrent
[       OK ] BatteryTest.TryChargingWithQueueAndNoCurrent (0 ms)
[----------] 8 tests from BatteryTest (0 ms total)

[----------] 5 tests from SimulatorTest
[ RUN      ] SimulatorTest.MakeConfigurationsCreatesCorrectNumber
[       OK ] SimulatorTest.MakeConfigurationsCreatesCorrectNumber (0 ms)
[ RUN      ] SimulatorTest.MakeVehiclesCreatesCorrectNumber
[       OK ] SimulatorTest.MakeVehiclesCreatesCorrectNumber (0 ms)
[ RUN      ] SimulatorTest.ConfigurationsHaveCorrectValues
[       OK ] SimulatorTest.ConfigurationsHaveCorrectValues (0 ms)
[ RUN      ] SimulatorTest.AssignChargerIsTriggeredWhenVehicleFinishesFlight
[       OK ] SimulatorTest.AssignChargerIsTriggeredWhenVehicleFinishesFlight (40 ms)
[ RUN      ] SimulatorTest.RunCompletesWithoutErrors
[       OK ] SimulatorTest.RunCompletesWithoutErrors (35 ms)
[----------] 5 tests from SimulatorTest (76 ms total)
[----------] Global test environment tear-down
[==========] 25 tests from 4 test suites ran. (133 ms total)
[  PASSED  ] 25 tests.
```
