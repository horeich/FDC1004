#include "mbed.h"
#include "mbed_trace.h"
#include "fdc1004.hpp"
#include "test.hpp"
#include "level_sensor.hpp"
#include "max31865.hpp"
#include "max31865_continuous.hpp"

int main(void)
{
  runFDC1004Test();
  levelSensor();
  MAX31865_Continuous maxObj;
  maxObj.Run();
}

