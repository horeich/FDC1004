// Copyright 2024 Fawad Siddiqui, Andreas Reichle (HOREICH GmbH)

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "fdc1004.hpp"

#define DEBUG 0

#define FDC1004Address 0b1010000 << 1
#define BYTE_TO_BINARY_PATTERN "%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\r\n"
#define BYTE_TO_BINARY_PATTERN_32 "%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\r\n"

#define BYTE_TO_BINARY(uint16_t)           \
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

#define BYTE_TO_BINARY_32(uint32_t)            \
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

FDC1004::FDC1004(mbed::I2C &i2c) : _i2c(i2c)
{
}

bool FDC1004::getManufacturerId()
{
    uint16_t manufacturerID = 0;
    readRegister(Register::manufacturerID, manufacturerID);
    if (manufacturerID != 0x5449)
    {
        return false;
    }
    return true;
}
bool FDC1004::getDeviceId()
{
    uint16_t deviceID = 0;
    readRegister(Register::deviceID, deviceID);
    if (deviceID != 0x1004)
    {
        return false;
    }
    return true;
}
bool FDC1004::reset()
{
    uint16_t value = 0;
    value |= (1 << 15);
    writeRegister(FDC1004::Register::ConfigRegister, value);
    if ((value & 0x8000))
        return true;
    else
        return false;
}

bool FDC1004::readRegister(Register regAddress, uint16_t &regValue)
{
    char registeraddress = static_cast<char>(regAddress);
    char data[2];
    int rc = _i2c.write(FDC1004Address, &registeraddress, 1, false); //<==true davor
    if (rc != 0)
    {
        printf("Failed i2c write\r\n");
        return false;
    }
    rc = _i2c.read(FDC1004Address, data, 2);
    if (rc != 0)
    {
        printf("Failed i2c read\r\n");
        return false;
    }

    uint16_t value = data[1];
    value = value | (data[0] << 8);
    regValue = value;

    return true;
}

bool FDC1004::writeRegister(FDC1004::Register reg, uint16_t regValue)
{
    char data[3];
    data[0] = (uint8_t)reg;
    data[1] = (char)(regValue >> 8);
    data[2] = (char)regValue;

    int rc = _i2c.write(address, &data[0], 3);
    if (rc != 0)
    {
        printf("Failed i2c write");
        return false;
    }
    return true;
}

bool FDC1004::getMeasurement(Register reg, uint32_t &value)
{
    uint16_t MSB, LSB;
    bool success1 = readRegister(reg, MSB);
    FDC1004::Register regLSB = static_cast<FDC1004::Register>(static_cast<int>(reg) + 1);
    bool success2 = readRegister(regLSB, LSB);
    value = LSB >> 8;
    value += MSB << 8;
    if (success1 && success2)
        return true;
    else
        return false;
}

bool FDC1004::setRepeatedMeasurements(bool enable)
{
    // readRegister
    uint16_t value = 0;
    readRegister(FDC1004::Register::ConfigRegister, value);
    if (enable)
    {
        value |= (1 << 8);
    }
    else
    {
        value |= (0 << 8);
    }
    writeRegister(FDC1004::Register::ConfigRegister, value);
    return true;
}

bool FDC1004::setMeasurementChannelConfig(FDC1004::Register measureConfigReg, FDC1004::Channel channelA, FDC1004::Channel channelB, uint8_t capdacValue)
{
    uint16_t value = 0x00;
    value |= ((uint16_t)channelA << 13);
    value |= ((uint16_t)channelB << 10);
    if (DEBUG)
    {
        if ((uint16_t)channelA >= (uint16_t)channelB)
        {
            printf("CHA cannot be smaller or equal to channel B\n");
            return false;
        }
        else if (channelA == FDC1004::Channel::CAPDAC)
        {
            printf("Capdac is not available in channel A\n");
            return false;
        }
    }
    if (channelB == FDC1004::Channel::CAPDAC)
    {
        if (capdacValue > 31)
        {
            printf("capdac value cannot be higher than 31\n");
            return false;
        }
        value |= (capdacValue << 5);
    }

    writeRegister(measureConfigReg, value);
    return true;
}

bool FDC1004::getMeasurementChannelConfig(FDC1004::Register configReg, FDC1004::Channel &channelA, FDC1004::Channel &channelB, uint8_t &capdacValue)
{
    uint16_t value = 0;
    bool success = readRegister(configReg, value);
    if (DEBUG)
    {
        printf("CONFIG REGISTER: " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(value));
    }
    uint16_t channelValue = 0;
    channelA = static_cast<Channel>(value >> 13);
    channelValue |= (value << 3);      // 0 0 1 1 0 0 1 0 1 0 0 0 0 0 0 0
    channelValue = channelValue >> 3;  // 1 0 0 1 0 1 0 0 0 0 0 0 0 0 0 0
    channelValue = channelValue >> 10; // 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0
    channelB = static_cast<Channel>(channelValue);
    capdacValue |= (value >> 5);    // 10010100
    capdacValue = capdacValue << 3; // 10100000
    capdacValue = capdacValue >> 3; // 00010100
    if (success)
        return true;
    else
        return false;
}

bool FDC1004::setMeasurementRate(FDC1004::MeasurementRate rate)
{
    uint16_t value = 0;
    readRegister(FDC1004::Register::ConfigRegister, value);

    value &= ~(0x03 << 10);
    value |= ((uint8_t)rate) << 10;

    if (rate == FDC1004::MeasurementRate::Rate100)
    {
        value |= (0 << 11);
        value |= (1 << 10);
    }
    else if (rate == FDC1004::MeasurementRate::Rate200)
    {
        value |= (1 << 11);
        value |= (0 << 10);
    }
    else if (rate == FDC1004::MeasurementRate::Rate400)
    {
        value |= (1 << 11);
        value |= (1 << 10);
    }

    bool success = writeRegister(Register::ConfigRegister, value);
    return success;
}

bool FDC1004::enableMeasurement(FDC1004::Channel CIN)
{
    uint16_t value = 0;
    readRegister(FDC1004::Register::ConfigRegister, value);
    switch (CIN)
    {
    case Channel::CIN1:
        value |= (1 << 7);
        break;
    case Channel::CIN2:
        value |= (1 << 6);
        break;
    case Channel::CIN3:
        value |= (1 << 5);
        break;
    case Channel::CIN4:
        value |= (1 << 4);
        break;
    default:
        printf("invalid measurement value");
        return false;
    }
    writeRegister(FDC1004::Register::ConfigRegister, value);
    return true;
}

bool FDC1004::isMeasurementEnabled(FDC1004::Channel CIN)
{
    uint16_t value = 0;
    readRegister(FDC1004::Register::ConfigRegister, value);
    switch (CIN)
    {
    case Channel::CIN1:
        if (value & 1 << 7)
            return 1;
        else
            return 0;
    case Channel::CIN2:
        if (value & 1 << 6)
            return 1;
        else
            return 0;
    case Channel::CIN3:
        if (value & 1 << 5)
            return 1;
        else
            return 0;
    case Channel::CIN4:
        if (value & 1 << 4)
            return 1;
        else
            return 0;
    default:
        printf("invalid measurement value");
    }
    return 0;
}

bool FDC1004::isMeasurementDone(FDC1004::Channel CIN)
{
    uint16_t value = 0;
    readRegister(FDC1004::Register::ConfigRegister, value);
    switch (CIN)
    {
    case Channel::CIN1:
        if (value & 1 << 3)
            return 1;
        else
            return 0;
    case Channel::CIN2:
        if (value & 1 << 2)
            return 1;
        else
            return 0;
    case Channel::CIN3:
        if (value & 1 << 1)
            return 1;
        else
            return 0;
    case Channel::CIN4:
        if (value & 1 << 0)
            return 1;
        else
            return 0;
    default:
        printf("invalid measurement value");
    }
    return 0;
}

bool FDC1004::disableMeasurement(FDC1004::Channel CIN)
{
    uint16_t value = 0;
    readRegister(FDC1004::Register::ConfigRegister, value);
    switch (CIN)
    {
    case Channel::CIN1:
        value |= (0 << 7);
        break;
    case Channel::CIN2:
        value |= (0 << 6);
        break;
    case Channel::CIN3:
        value |= (0 << 5);
        break;
    case Channel::CIN4:
        value |= (0 << 4);
        break;
    default:
        printf("invalid measurement value");
        return false;
    }
    writeRegister(FDC1004::Register::ConfigRegister, value);
    return true;
}

bool FDC1004::measure(Channel CIN)
{
    uint32_t measure;
    bool success;
    switch (CIN)
    {
    case Channel::CIN1:
        success = getMeasurement(Register::meas1MSBreg, measure);
        if (success)
            break;
        else
        {
            if (DEBUG)
                printf("Unable to get measurement\n");
            return false;
        }
    case Channel::CIN2:
        success = getMeasurement(Register::meas2MSBreg, measure);
        if (success)
            break;
        else
        {
            if (DEBUG)
                printf("Unable to get measurement\n");
            return false;
        }
    case Channel::CIN3:
        success = getMeasurement(Register::meas3MSBreg, measure);
        if (success)
            break;
        else
        {
            if (DEBUG)
                printf("Unable to get measurement\n");
            return false;
        }
    case Channel::CIN4:
        success = getMeasurement(Register::meas4MSBreg, measure);
        if (success)
            break;
        else
        {
            if (DEBUG)
                printf("Unable to get measurement\n");
            return false;
        }
    default:
        printf("Invalid Channel \n");
        return false;
    }
    if (DEBUG)
    {
        if (isMeasurementDone(CIN))
        {
            printf("Measurement of CHANNEL %d is done\n", ((int)CIN + 1));
        }
    }

    printf("Measure%d: %fpF\r\n", static_cast<int>(CIN) + 1, (measure / pow(2, 19)));

    wait_us(1000 * 1000);

    return true;
}

bool FDC1004::setGainCalibration(float gain, FDC1004::Register reg)
{
    if (gain >= 4 || gain < 0)
        return 0;
    uint16_t value = 0;
    value = gain * (pow(2, 14));
    writeRegister(reg, value);
    return true;
}

bool FDC1004::getGainCalibration(FDC1004::Register reg, float &gain)
{
    uint16_t value = 0;
    bool success = readRegister(reg, value);
    gain = value / pow(2, 14);
    if (success)
        return true;
    else
        return false;
}

bool FDC1004::setOffsetCalibration(float offset, FDC1004::Register reg)
{
    if (offset >= 16 || offset <= -16)
        return 0;
    offset = (0.5 * offset) + 8;
    uint16_t value = 0;
    value = offset * (pow(2, 11));
    writeRegister(reg, value);
    return true;
}

bool FDC1004::getOffsetCalibration(FDC1004::Register reg, float &offset)
{
    uint16_t value = 0;
    bool success = readRegister(reg, value);
    offset = (value / pow(2, 11) - 8) * 2;
    if (success)
        return true;
    else
        return false;
}

bool FDC1004::init()
{
    uint16_t value = 0;
    bool success1 = readRegister(FDC1004::Register::ConfigRegister, value);
    if (DEBUG)
    {
        printf("CONFIG REGISTER YY: " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(value));
    }
    reset();

    bool success2 = readRegister(FDC1004::Register::ConfigRegister, value);

    while ((value & 0x8000) != 0)
    {

        // wait_us(3000*1000);
    }
    bool success3 = setRepeatedMeasurements(true);
    if (DEBUG)
        printf("After reset, only repeated " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(value));
    bool success4 = setMeasurementRate(FDC1004::MeasurementRate::Rate100);
    uint16_t testausgabe_config1 = 0;
    bool success5 = readRegister(FDC1004::Register::ConfigRegister, testausgabe_config1);
    printf("Configurationsregister :  " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(testausgabe_config1));
    if (success1 && success2 && success3 && success4 && success5)
        return true;
    else
        return false;
}
