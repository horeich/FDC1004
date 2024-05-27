#include "mbed.h"
#include "mbed_trace.h"
#include "fdc1004.hpp"
#include "test.hpp"

#define MBED_CONF_FDC1004_DEBUG 1
#if MBED_CONF_FDC1004_DEBUG == 1

#define BYTE_TO_BINARY_PATTERN "%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\r\n"
#define BYTE_TO_BINARY_PATTERN_32 "%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\r\n"
#define BYTE_TO_BINARY(uint16_t)         \
  ((uint16_t) & 0x8000 ? '1' : '0'),     \
      ((uint16_t) & 0x4000 ? '1' : '0'), \
      ((uint16_t) & 0x2000 ? '1' : '0'), \
      ((uint16_t) & 0x1000 ? '1' : '0'), \
      ((uint16_t) & 0x800 ? '1' : '0'),  \
      ((uint16_t) & 0x400 ? '1' : '0'),  \
      ((uint16_t) & 0x200 ? '1' : '0'),  \
      ((uint16_t) & 0x100 ? '1' : '0'),  \
      ((uint16_t) & 0x80 ? '1' : '0'),   \
      ((uint16_t) & 0x40 ? '1' : '0'),   \
      ((uint16_t) & 0x20 ? '1' : '0'),   \
      ((uint16_t) & 0x10 ? '1' : '0'),   \
      ((uint16_t) & 0x08 ? '1' : '0'),   \
      ((uint16_t) & 0x04 ? '1' : '0'),   \
      ((uint16_t) & 0x02 ? '1' : '0'),   \
      ((uint16_t) & 0x01 ? '1' : '0')

#define BYTE_TO_BINARY_32(uint32_t)          \
  ((uint32_t) & 0x800000000 ? '1' : '0'),    \
      ((uint32_t) & 0x40000000 ? '1' : '0'), \
      ((uint32_t) & 0x20000000 ? '1' : '0'), \
      ((uint32_t) & 0x10000000 ? '1' : '0'), \
      ((uint32_t) & 0x8000000 ? '1' : '0'),  \
      ((uint32_t) & 0x4000000 ? '1' : '0'),  \
      ((uint32_t) & 0x2000000 ? '1' : '0'),  \
      ((uint32_t) & 0x1000000 ? '1' : '0'),  \
      ((uint32_t) & 0x800000 ? '1' : '0'),   \
      ((uint32_t) & 0x400000 ? '1' : '0'),   \
      ((uint32_t) & 0x200000 ? '1' : '0'),   \
      ((uint32_t) & 0x100000 ? '1' : '0'),   \
      ((uint32_t) & 0x80000 ? '1' : '0'),    \
      ((uint32_t) & 0x40000 ? '1' : '0'),    \
      ((uint32_t) & 0x20000 ? '1' : '0'),    \
      ((uint32_t) & 0x10000 ? '1' : '0'),    \
      ((uint32_t) & 0x8000 ? '1' : '0'),     \
      ((uint32_t) & 0x4000 ? '1' : '0'),     \
      ((uint32_t) & 0x2000 ? '1' : '0'),     \
      ((uint32_t) & 0x1000 ? '1' : '0'),     \
      ((uint32_t) & 0x800 ? '1' : '0'),      \
      ((uint32_t) & 0x400 ? '1' : '0'),      \
      ((uint32_t) & 0x200 ? '1' : '0'),      \
      ((uint32_t) & 0x100 ? '1' : '0'),      \
      ((uint32_t) & 0x80 ? '1' : '0'),       \
      ((uint32_t) & 0x40 ? '1' : '0'),       \
      ((uint32_t) & 0x20 ? '1' : '0'),       \
      ((uint32_t) & 0x10 ? '1' : '0'),       \
      ((uint32_t) & 0x08 ? '1' : '0'),       \
      ((uint32_t) & 0x04 ? '1' : '0'),       \
      ((uint32_t) & 0x02 ? '1' : '0'),       \
      ((uint32_t) & 0x01 ? '1' : '0')

#define debug_print(...) printf(__VA_ARGS__)
#else
#define debug_print(...)
#endif

using namespace mbed;
// I2C i2c(PC_1, PC_0);
void runFDC1004Test()
{
  I2C i2c(PC_1, PC_0);
  FDC1004 fdc1004(i2c);
  bool success0 = fdc1004.init();
  bool success1, success2, success3;
  success1 = fdc1004.setRepeatedMeasurements(true);
  success2 = fdc1004.setMeasurementRate(FDC1004::MeasurementRate::Rate100);
  if (success0 && success1 && success2)
    debug_print("Repeated measurements and measurement rate has been set\n");
  else
    debug_print("Could not set the repeated measurements and/or measurement rate\n");
  bool manufacturerId, deviceId;
  manufacturerId = fdc1004.getManufacturerId();
  if (manufacturerId)
  {
    debug_print("Manufacturer Id is correct\n");
  }
  deviceId = fdc1004.getDeviceId();
  if (deviceId)
  {
    debug_print("Device ID Id is correct\n");
  }
  // below you may enable any channel combination according to these constraints (CHA cannot be CAPDAC, CHA cannot be grater than CHB, and CAPDAC is neither available on CHA nor it can be set greater than 31)
  success1 = fdc1004.setMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg1, FDC1004::Channel::CIN1, FDC1004::Channel::DISABLED, 1);
  success2 = fdc1004.setMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg1, FDC1004::Channel::CIN2, FDC1004::Channel::DISABLED);
  success3 = fdc1004.setMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg1, FDC1004::Channel::CIN3, FDC1004::Channel::DISABLED);
  if (success1 && success2 && success3)
  {
    debug_print("Measurement configuration register has been configured\n");
  }
  FDC1004::Channel channelA;
  FDC1004::Channel channelB;
  uint8_t capdacValue = 0;
  fdc1004.getMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg1, channelA, channelB, capdacValue);
  if (channelA == static_cast<FDC1004::Channel>(static_cast<int>(FDC1004::Channel::CIN2) + 1) && channelB == FDC1004::Channel::DISABLED)
  {
    debug_print("Channel succesfully set\n");
  }
  else
  {
    // debug_print("%04x\n%04x\n%d\n", (uint16_t)channelA, (uint16_t)channelB, (int)capdacValue);
    debug_print("Failed to set channel\n");
  }

  fdc1004.enableMeasurement(FDC1004::Channel::CIN2);
  fdc1004.enableMeasurement(FDC1004::Channel::CIN1);
  fdc1004.enableMeasurement(FDC1004::Channel::CIN3);
  if (fdc1004.isMeasurementEnabled(FDC1004::Channel::CIN1) && fdc1004.isMeasurementEnabled(FDC1004::Channel::CIN2) && fdc1004.isMeasurementEnabled(FDC1004::Channel::CIN3))
  {
    debug_print("CHANNELS %d, %d, %d are enabled\n", (static_cast<int>(FDC1004::Channel::CIN1) + 1), (static_cast<int>(FDC1004::Channel::CIN2) + 1), (static_cast<int>(FDC1004::Channel::CIN3) + 1));
  }
  else
  {
    debug_print("Measurement is not enabled\n");
  }
  fdc1004.setGainCalibration(2.314f, FDC1004::Register::GainCal2reg);
  fdc1004.setOffsetCalibration(6.92f, FDC1004::Register::OffsetCal1reg);

  float gain = 0;
  fdc1004.getGainCalibration(FDC1004::Register::GainCal2reg, gain);
  debug_print("the gain calibration of CIN1 is %.3f\n", gain);
  float offset = 0;
  fdc1004.getOffsetCalibration(FDC1004::Register::OffsetCal1reg, offset);
  debug_print("the offset calibration of CIN1 is %.3f\n", offset);
}
