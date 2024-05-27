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
        Meas1MSBreg=0x00,
        Meas1LSBreg=0x01,
        Meas2MSBreg=0x02,
        Meas2LSBreg=0x03,
        Meas3MSBreg=0x04,
        Meas3LSBreg=0x05,
        Meas4MSBreg=0x06,
        Meas4LSBreg=0x07,
        ConfigMeasurementReg1 = 0x08,
        ConfigMeasurementReg2 = 0x09,
        ConfigMeasurementReg3 = 0x0A,
        ConfigMeasurementReg4 = 0x0B,
        ConfigRegister = 0x0C,
        GainCal1reg = 0x11,
        GainCal2reg = 0x12,
        GainCal3reg = 0x13,
        GainCal4reg = 0x14,
        OffsetCal1reg = 0x0D,
        OffsetCal2reg = 0x0E,
        OffsetCal3reg = 0x0F,
        OffsetCal4reg = 0x10,
        ManufacturerID = 0xFE,
        DeviceID = 0xFF
    };

public:
    

    FDC1004(mbed::I2C& i2c);

    bool init();
    bool readMeasurement(Channel CIN,float& measurementValue);
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
    bool readMeasurementRaw(Register reg, uint32_t& value);
    bool getGainCalibration(FDC1004::Register reg, float& gain);
    bool getOffsetCalibration(FDC1004::Register reg,float& offset);

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
    bool readRegister(Register regAddress, uint16_t& regValue);

    mbed::I2C& _i2c;
    
};

#endif