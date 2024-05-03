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
  
}
