#include "mbed.h"
#include "mbed_trace.h"
#include "fuell.hpp"

using namespace mbed;
#define DEBUG 0
//I2C i2c(D14, D15);  für kabel
I2C i2c(PC_1, PC_0);


int main(void)
{

  FDC1004 fdc1004(i2c);
  fdc1004.init();
  if(DEBUG)
  {
    bool manufacturerId, deviceId;
    manufacturerId= fdc1004.getManufacturerId();
    if (manufacturerId)
    {
        printf("Manufacturer Id is incorrect\n");
    }
    deviceId= fdc1004.getDeviceId();
    if (deviceId)
    {
        printf("Device ID Id is incorrect\n");
    }
  }
  // below you may enable any channel combination according to these constraints (CHA cannot be CAPDAC, CHA cannot be grater than CHB, and CAPDAC is neither available on CHA nor it can be set greater than 31)
  bool success1=fdc1004.setMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg1, FDC1004::Channel::CIN1, FDC1004::Channel::DISABLED,1);
  bool success2=fdc1004.setMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg1, FDC1004::Channel::CIN2, FDC1004::Channel::DISABLED);
  bool success3=fdc1004.setMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg1, FDC1004::Channel::CIN3, FDC1004::Channel::DISABLED);
  if(DEBUG)
  {
    if(success1 && success2 && success3)
    {
      printf("Measurement configuration register has been configured\n");
    }
  FDC1004::Channel channelA;
  FDC1004::Channel channelB;
  uint8_t capdacValue = 0;
  fdc1004.getMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg1, channelA, channelB, capdacValue);
  if(channelA == FDC1004::Channel::CIN2 && channelB == FDC1004::Channel::CAPDAC)
  {
    printf("Channel succesfully set\n");
  }
  else
  {
    printf("%04x\n%04x\n%d\n",(uint16_t)channelA,(uint16_t)channelB,(int)capdacValue);
  }
  }
  fdc1004.enableMeasurement(FDC1004::Channel::CIN2);
  fdc1004.enableMeasurement(FDC1004::Channel::CIN1);
  fdc1004.enableMeasurement(FDC1004::Channel::CIN3);
  if(DEBUG)
  {
    if (fdc1004.isMeasurementEnabled(FDC1004::Channel::CIN2))
    {
        printf("CHANNEL %d is enabled\n",((int)FDC1004::Channel::CIN2+1));
    }
    else
    {
      printf("Measurement is not enabled\n");
    }
  
  // uncomment the below lines if one wants to calibrate the gain and the offset
  // fdc1004.setGainCalibration(2.314f, FDC1004::Register::gainCal2reg);   
  // fdc1004.setOffsetCalibration(6.92f, FDC1004::Register::offsetCal1reg);
  
    float gain = 0;
    fdc1004.getGainCalibration(FDC1004::Register::gainCal2reg,gain);
    printf("the gain calibration of CIN1 is %.3f\n",gain);
    float offset = 0;
    fdc1004.getOffsetCalibration(FDC1004::Register::offsetCal1reg,offset);
    printf("the offset calibration of CIN1 is %.3f\n",offset);
  }
  wait_us(100*1000);
  while(1)
  {
    fdc1004.measure(FDC1004::Channel::CIN1);
    fdc1004.measure(FDC1004::Channel::CIN2);
    fdc1004.measure(FDC1004::Channel::CIN3);
  }
}
