#ifndef FDC1004_HPP
#define FDC1004_HPP

#include <stdio.h>
#include "InterruptIn.h"
#include "mbed.h"
#include "I2C.h"

class FDC1004
{
    static constexpr uint8_t address = 0b1010000 << 1;

public:
    enum class Channel : uint8_t 
    {
        CIN1 = 0,
        CIN2 = 1,
        CIN3 = 2,
        CIN4 = 3,
        CAPDAC = 4,
        DISABLED = 7,
    };
    
    enum class MeasurementRate : uint8_t
    {
        Rate100 = 1,
        Rate200 = 2,
        Rate400 = 3,
    };
    
    enum class Register : uint8_t
    {
        meas1MSBreg=0x00,
        meas1LSBreg=0x01,
        meas2MSBreg=0x02,
        meas2LSBreg=0x03,
        meas3MSBreg=0x04,
        meas3LSBreg=0x05,
        meas4MSBreg=0x06,
        meas4LSBreg=0x07,
        ConfigMeasurementReg1 = 0x08,
        ConfigMeasurementReg2 = 0x09,
        ConfigMeasurementReg3 = 0x0A,
        ConfigMeasurementReg4 = 0x0B,
        ConfigRegister = 0x0C,
        gainCal1reg = 0x11,
        gainCal2reg = 0x12,
        gainCal3reg = 0x13,
        gainCal4reg = 0x14,
        offsetCal1reg = 0x0D,
        offsetCal2reg = 0x0E,
        offsetCal3reg = 0x0F,
        offsetCal4reg = 0x10,
        manufacturerID = 0xFE,
        deviceID = 0xFF
    };

public:
    

    FDC1004(mbed::I2C& i2c);

    bool init();
    bool measure(Channel CIN);
    bool getManufacturerId();
    bool getDeviceId();
    bool setMeasurementRate(FDC1004::MeasurementRate rate);
    bool reset();
    bool setRepeatedMeasurements(bool );
    bool enableMeasurement(FDC1004::Channel CIN );
    bool isMeasurementEnabled(FDC1004::Channel CIN);
    bool isMeasurementDone(FDC1004::Channel CIN);
    bool disableMeasurement(FDC1004::Channel CIN);
    bool setGainCalibration(float gain, FDC1004::Register reg);
    bool setOffsetCalibration(float offset,FDC1004::Register reg );
    bool getMeasurement(Register reg, uint32_t& value);
    bool getGainCalibration(FDC1004::Register reg, float& gain);
    bool getOffsetCalibration(FDC1004::Register reg,float& offset);

    bool readRegister(Register regAddress, uint16_t& regValue);

    bool setMeasurementChannelConfig(
        
        FDC1004::Register configReg, 
        FDC1004::Channel channelA, 
        FDC1004::Channel channelB,
        uint8_t capdacValue = 0);

    bool getMeasurementChannelConfig(FDC1004::Register configReg, FDC1004::Channel& channelA, FDC1004::Channel& channelB, uint8_t& capdacValue);

    void level_sensor(void);
    void test();

private:    

    bool writeRegister(FDC1004::Register register, uint16_t value);//uint16_t value daovor, test 

    mbed::I2C& _i2c;
    
};

#endif