#include "mbed.h"
#include "mbed_trace.h"
#include "fdc1004.hpp"

using namespace mbed;
I2C i2c(PC_1, PC_0);
void levelSensor(void)
{
  FDC1004 fdc1004(i2c);
  uint16_t value =0;
  fdc1004.reset();
  fdc1004.readRegister(FDC1004::Register::ConfigRegister,value);
  //here it is being read if the reset bit has been set back to 0
  while ((value & 0x8000) != 0)
  {
    // wait_us(3000*1000);
  }

  //below you may enable or disable the set repeated measurements
  fdc1004.setRepeatedMeasurements(true);

  //below you may set the desired measurement rate (100S/s,200S/s,400S/s)
  fdc1004.setMeasurementRate(FDC1004::MeasurementRate::Rate100);

  // below you may configure measurement channel combination according to these constraints (CHA cannot be CAPDAC, CHA cannot be grater than CHB, and CAPDAC is neither available on CHA nor it can be set greater than 31)
  fdc1004.setMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg1, FDC1004::Channel::CIN1, FDC1004::Channel::DISABLED,1);
  fdc1004.setMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg1, FDC1004::Channel::CIN2, FDC1004::Channel::DISABLED);
  fdc1004.setMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg1, FDC1004::Channel::CIN3, FDC1004::Channel::DISABLED);

  //you may enable any channel for measurement
  fdc1004.enableMeasurement(FDC1004::Channel::CIN2);
  fdc1004.enableMeasurement(FDC1004::Channel::CIN1);
  fdc1004.enableMeasurement(FDC1004::Channel::CIN3);

  wait_us(100*1000);
  while(1)
  {
    //measure the relevant channels according to the schematic
    fdc1004.measure(FDC1004::Channel::CIN1);
    fdc1004.measure(FDC1004::Channel::CIN2);
    fdc1004.measure(FDC1004::Channel::CIN3);
  }
}