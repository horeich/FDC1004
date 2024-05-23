#include "mbed.h"
#include "mbed_trace.h"
#include "fdc1004.hpp"
#include "test.hpp"

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

using namespace mbed;
// I2C i2c(PC_1, PC_0);
void runFDC1004Test()
{
  I2C i2c(PC_1, PC_0);
  FDC1004 fdc1004(i2c);
  uint16_t value = 0;
  bool success1 = fdc1004.readRegister(FDC1004::Register::ConfigRegister, value);
  printf("CONFIG REGISTER YY: " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(value));
  fdc1004.reset();
  bool success2 = fdc1004.readRegister(FDC1004::Register::ConfigRegister, value);
  while ((value & 0x8000) != 0)
  {
    // wait_us(3000*1000);
  }
  bool success3 = fdc1004.setRepeatedMeasurements(true);
  printf("After reset, only repeated " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(value));
  bool success4 = fdc1004.setMeasurementRate(FDC1004::MeasurementRate::Rate100);
  uint16_t testausgabe_config1 = 0;
  bool success5 = fdc1004.readRegister(FDC1004::Register::ConfigRegister, testausgabe_config1);
  printf("Configurationsregister :  " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(testausgabe_config1));
  if (success1 && success2 && success3 && success4 && success5)
    printf("Repeated measurements and measurement rate has been set\n");
  else
    printf("Could not set the repeated measurements and/or measurement rate\n");
  bool manufacturerId, deviceId;
  manufacturerId = fdc1004.getManufacturerId();
  if (manufacturerId)
  {
    printf("Manufacturer Id is incorrect\n");
  }
  deviceId = fdc1004.getDeviceId();
  if (deviceId)
  {
    printf("Device ID Id is incorrect\n");
  }
  // below you may enable any channel combination according to these constraints (CHA cannot be CAPDAC, CHA cannot be grater than CHB, and CAPDAC is neither available on CHA nor it can be set greater than 31)
  success1 = fdc1004.setMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg1, FDC1004::Channel::CIN1, FDC1004::Channel::DISABLED, 1);
  success2 = fdc1004.setMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg1, FDC1004::Channel::CIN2, FDC1004::Channel::DISABLED);
  success3 = fdc1004.setMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg1, FDC1004::Channel::CIN3, FDC1004::Channel::DISABLED);
  if (success1 && success2 && success3)
  {
    printf("Measurement configuration register has been configured\n");
  }
  FDC1004::Channel channelA;
  FDC1004::Channel channelB;
  uint8_t capdacValue = 0;
  fdc1004.getMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg1, channelA, channelB, capdacValue);
  if (channelA == FDC1004::Channel::CIN2 && channelB == FDC1004::Channel::CAPDAC)
  {
    printf("Channel succesfully set\n");
  }
  else
  {
    printf("%04x\n%04x\n%d\n", (uint16_t)channelA, (uint16_t)channelB, (int)capdacValue);
  }

  fdc1004.enableMeasurement(FDC1004::Channel::CIN2);
  fdc1004.enableMeasurement(FDC1004::Channel::CIN1);
  fdc1004.enableMeasurement(FDC1004::Channel::CIN3);
  if (fdc1004.isMeasurementEnabled(FDC1004::Channel::CIN2))
  {
    printf("CHANNEL %d is enabled\n", ((int)FDC1004::Channel::CIN2 + 1));
  }
  else
  {
    printf("Measurement is not enabled\n");
  }
  fdc1004.setGainCalibration(2.314f, FDC1004::Register::gainCal2reg);
  fdc1004.setOffsetCalibration(6.92f, FDC1004::Register::offsetCal1reg);

  float gain = 0;
  fdc1004.getGainCalibration(FDC1004::Register::gainCal2reg, gain);
  printf("the gain calibration of CIN1 is %.3f\n", gain);
  float offset = 0;
  fdc1004.getOffsetCalibration(FDC1004::Register::offsetCal1reg, offset);
  printf("the offset calibration of CIN1 is %.3f\n", offset);
}

// void FDC1004::test(void)
// {
//   uint16_t value =0;
//   bool success1=readRegister(FDC1004::Register::ConfigRegister,value);
//   printf("CONFIG REGISTER YY: " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(value));
//   reset();
//   bool success2=readRegister(FDC1004::Register::ConfigRegister,value);
//   while ((value & 0x8000) != 0)
//   {
//     // wait_us(3000*1000);
//   }
//   bool success3=setRepeatedMeasurements(true);
//   printf("After reset, only repeated " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(value));
//   bool success4=setMeasurementRate(FDC1004::MeasurementRate::Rate100);
//   uint16_t testausgabe_config1 = 0;
//   bool success5=readRegister(FDC1004::Register::ConfigRegister,testausgabe_config1);
//   printf("Configurationsregister :  " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(testausgabe_config1));
//   if(success1 && success2 && success3 && success4 && success5)
//     printf("Repeated measurements and measurement rate has been set\n");
//   else
//     printf("Could not set the repeated measurements and/or measurement rate\n");
//   bool manufacturerId, deviceId;
//   manufacturerId= getManufacturerId();
//   if (manufacturerId)
//   {
//       printf("Manufacturer Id is incorrect\n");
//   }
//   deviceId= getDeviceId();
//   if (deviceId)
//   {
//       printf("Device ID Id is incorrect\n");
//   }
//   // below you may enable any channel combination according to these constraints (CHA cannot be CAPDAC, CHA cannot be grater than CHB, and CAPDAC is neither available on CHA nor it can be set greater than 31)
//   bool success1=setMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg1, FDC1004::Channel::CIN1, FDC1004::Channel::DISABLED,1);
//   bool success2=setMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg1, FDC1004::Channel::CIN2, FDC1004::Channel::DISABLED);
//   bool success3=setMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg1, FDC1004::Channel::CIN3, FDC1004::Channel::DISABLED);
//   if(success1 && success2 && success3)
//   {
//     printf("Measurement configuration register has been configured\n");
//   }
//   FDC1004::Channel channelA;
//   FDC1004::Channel channelB;
//   uint8_t capdacValue = 0;
//   getMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg1, channelA, channelB, capdacValue);
//   if(channelA == FDC1004::Channel::CIN2 && channelB == FDC1004::Channel::CAPDAC)
//   {
//     printf("Channel succesfully set\n");
//   }
//   else
//   {
//     printf("%04x\n%04x\n%d\n",(uint16_t)channelA,(uint16_t)channelB,(int)capdacValue);
//   }

//   enableMeasurement(FDC1004::Channel::CIN2);
//   enableMeasurement(FDC1004::Channel::CIN1);
//   enableMeasurement(FDC1004::Channel::CIN3);
//   if (isMeasurementEnabled(FDC1004::Channel::CIN2))
//   {
//       printf("CHANNEL %d is enabled\n",((int)FDC1004::Channel::CIN2+1));
//   }
//   else
//   {
//     printf("Measurement is not enabled\n");
//   }
//   setGainCalibration(2.314f, FDC1004::Register::gainCal2reg);
//   setOffsetCalibration(6.92f, FDC1004::Register::offsetCal1reg);

//   float gain = 0;
//   getGainCalibration(FDC1004::Register::gainCal2reg,gain);
//   printf("the gain calibration of CIN1 is %.3f\n",gain);
//   float offset = 0;
//   getOffsetCalibration(FDC1004::Register::offsetCal1reg,offset);
//   printf("the offset calibration of CIN1 is %.3f\n",offset);
// }
