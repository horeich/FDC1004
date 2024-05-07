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
        offsetCal4reg = 0x10
    };

public:
    

    FDC1004(mbed::I2C& i2c);

    void init();
    void measure();
    uint16_t getManufacturerId();
    uint16_t getDeviceId();
    bool setConfigurationRegister();
    void setMeasurementRate(FDC1004::MeasurementRate rate);
    void reset();
    void measurementRate(uint16_t& value, uint16_t rate);
    void setRepeatedMeasurements(bool set);
    bool enableMeasurement(FDC1004::Channel CIN );
    bool isMeasurementEnabled(FDC1004::Channel CIN);
    bool isMeasurementDone(FDC1004::Channel CIN);
    void disableMeasurement(FDC1004::Channel CIN);
    bool setGainCalibration(float gain, FDC1004::Register reg);
    float getGainCalibration(FDC1004::Register reg);
    bool setOffsetCalibration(float offset,FDC1004::Register reg );
    float getOffsetCalibration(FDC1004::Register reg);
    float convert2Decimal24(uint32_t rawdata);
    float getOffsetCalibration();

    uint16_t readRegister(char registeraddress);
    uint16_t getConfigRegister();

    uint32_t getMeasure1();
    uint32_t getMeasure2();
    uint32_t getMeasure3();
    uint32_t getMeasure4();

    void setRegisterBit(uint16_t& value, u_int8_t position, uint8_t bit, char registeraddress);
    void setConfigRegisterBit(uint16_t& value, u_int8_t position, uint8_t bit);


    void setConfMeas1Bit(uint16_t& value, u_int8_t position, uint8_t bit);
    void setConfMeas2Bit(uint16_t& value, u_int8_t position, uint8_t bit);
    void setConfMeas3Bit(uint16_t& value, u_int8_t position, uint8_t bit);
    void setConfMeas4Bit(uint16_t& value, u_int8_t position, uint8_t bit);

    
    void activateDifferentialMeasurements1(uint16_t& value);
    void activateDifferentialMeasurements2(uint16_t& value);
    void activateDifferentialMeasurements3(uint16_t& value);
    void activateDifferentialMeasurements4(uint16_t& value);

    bool setMeasurementChannelConfig(
        
        FDC1004::Register configReg, 
        FDC1004::Channel channelA, 
        FDC1004::Channel channelB,
        uint8_t capdacValue = 0);

    bool setMeasurementOffsetCapacitance(FDC1004::Register configReg, uint8_t offset);




private:    

    void writeRegister(FDC1004::Register register, uint16_t& value);//uint16_t value daovor, test 

    mbed::I2C& _i2c;
    
};

#endif