#include "mbed.h"
#include "mbed_trace.h"
#include "fuell.hpp"

using namespace mbed;

//I2C i2c(D14, D15);  für kabel
I2C i2c(PC_1, PC_0);


int main(void)
{
  FDC1004::Channel channelToMeasure=FDC1004::Channel::CIN2;
  FDC1004 fdc1004(i2c);
  fdc1004.init();
  uint16_t manufacturerId, deviceId;
  manufacturerId= fdc1004.getManufacturerId();
  if (manufacturerId == 0x5449)
  {
      printf("Manufacturer Id is correct\n");
  }
  deviceId= fdc1004.getDeviceId();
  if (deviceId == 0x1004)
  {
      printf("Device Id is correct\n");
  }
  fdc1004.enableMeasurement(channelToMeasure);
  if (fdc1004.isMeasurementEnabled(channelToMeasure))
  {
      printf("CHANNEL %d is enabled\n",((int)channelToMeasure+1));
      wait_us(100*1000);
  }
  else
  {
    printf("Measurement is not enabled\n");
  }
    // while(1)
    // {
    fdc1004.measure();
    // }
  if (fdc1004.isMeasurementDone(channelToMeasure))
  {
    printf("Measurement of CHANNEL %d is done\n",((int)channelToMeasure+1));
  }
  fdc1004.setGainCalibration(2.314f, FDC1004::Register::gainCal2reg);
  float gain = fdc1004.getGainCalibration(FDC1004::Register::gainCal2reg);
  printf("the gain calibration of CIN1 is %.3f\n",gain);
  fdc1004.setOffsetCalibration(6.92f, FDC1004::Register::offsetCal1reg);
  float offset = fdc1004.getOffsetCalibration(FDC1004::Register::offsetCal1reg);
  printf("the offset calibration of CIN1 is %.3f\n",offset);


  
}
