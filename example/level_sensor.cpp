#include "mbed.h"
#include "mbed_trace.h"
#include "fdc1004.hpp"

using namespace mbed;
I2C i2c(PC_1, PC_0);
void levelSensor(void)
{
  FDC1004 fdc1004(i2c);
  uint16_t value = 0;
  fdc1004.reset();
  wait_us(1000*1000);
  // below you may enable or disable the set repeated measurements
  fdc1004.setRepeatedMeasurements(true);

  // below you may set the desired measurement rate (100S/s,200S/s,400S/s)
  fdc1004.setMeasurementRate(FDC1004::MeasurementRate::Rate100);

  // below you may configure measurement channel combination according to these constraints (CHA cannot be CAPDAC, CHA cannot be grater than CHB, and CAPDAC is neither available on CHA nor it can be set greater than 31)
  fdc1004.setMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg1, FDC1004::Channel::CIN1, FDC1004::Channel::DISABLED, 1);
  fdc1004.setMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg1, FDC1004::Channel::CIN2, FDC1004::Channel::DISABLED);
  fdc1004.setMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg1, FDC1004::Channel::CIN3, FDC1004::Channel::DISABLED);

  // you may enable any channel for measurement
  fdc1004.enableMeasurement(FDC1004::Channel::CIN2);
  fdc1004.enableMeasurement(FDC1004::Channel::CIN1);
  fdc1004.enableMeasurement(FDC1004::Channel::CIN3);

  wait_us(100 * 1000);
  float measurementValue=0;
  while (1)
  {
    // measure the relevant channels according to the schematic
    fdc1004.readMeasurement(FDC1004::Channel::CIN1,measurementValue);
    printf("Measure 1: %f\n", measurementValue);
    fdc1004.readMeasurement(FDC1004::Channel::CIN2,measurementValue);
    printf("Measure 2: %f\n", measurementValue);
    fdc1004.readMeasurement(FDC1004::Channel::CIN3,measurementValue);
    printf("Measure 3: %f\n", measurementValue);
  }
}