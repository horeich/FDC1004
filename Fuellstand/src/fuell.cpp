#include "fuell.hpp"

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
//_alert(PC_12, PinMode::PullNone),

// interrupt_triggered(true),//true
// high_limit_reached(false)
{
}

uint16_t FDC1004::getConfigRegister()
{
    return readRegister(0x0C);
}
uint16_t FDC1004::getManufacturerId()
{
    return readRegister(0xFE);
}

uint16_t FDC1004::getDeviceId()
{
    return readRegister(0xFF);
}
void FDC1004::reset()
{

    uint16_t value = 0;
    setConfigRegisterBit(value, 15, 1);
}

uint16_t FDC1004::readRegister(char registeraddress)
{

    // printf("FDC1004::%s\r\n", __func__);
    // uint8_t FDC1004Address = 0b1010000 << 1;

    char data[2];
    int rc = _i2c.write(FDC1004Address, &registeraddress, 1, false); //<==true davor
    if (rc != 0)
    {

        printf("Fehler i2c write\r\n");
    }
    rc = _i2c.read(FDC1004Address, data, 2);
    if (rc != 0)
    {

        printf("Fehler i2c read\r\n");
    }

    uint16_t value = data[1];
    value = value | (data[0] << 8);

    return value;
}

uint32_t FDC1004::getMeasure1()
{
    uint16_t meas1_MSB = readRegister(0x00);
    uint16_t meas1_LSB = readRegister(0x01);
    uint32_t complete_measure_binary1 = meas1_LSB >> 8;
    complete_measure_binary1 += meas1_MSB<< 8;
    return complete_measure_binary1;
}

uint32_t FDC1004::getMeasure2()
{
    uint16_t meas2_MSB = readRegister(0x02);
    uint16_t meas2_LSB = readRegister(0x03);
    uint32_t complete_measure_binary2 = meas2_LSB >> 8;
    complete_measure_binary2 += meas2_MSB << 8;
    return complete_measure_binary2;
}
uint32_t FDC1004::getMeasure3()
{
    uint16_t meas3_MSB = readRegister(0x04);
    uint16_t meas3_LSB = readRegister(0x05);
    uint32_t complete_measure_binary3 = meas3_LSB >> 8;
    complete_measure_binary3 += meas3_MSB << 8;
    return complete_measure_binary3;
}
uint32_t FDC1004::getMeasure4()
{
    uint16_t meas4_MSB = readRegister(0x06);
    uint16_t meas4_LSB = readRegister(0x07);
    uint32_t complete_measure_binary4 = meas4_LSB >> 8;
    complete_measure_binary4 += meas4_MSB << 8;
    return complete_measure_binary4;
}

void FDC1004::setRepeatedMeasurements(bool set)
{
    // readRegister
    uint16_t value = 0;
    if (set) 
    {
        setConfigRegisterBit(value, 8, 1);
    }
    else
    {
        setConfigRegisterBit(value, 8, 0);
    }
    // writeRegister(ConfigRegister, value);
}

void FDC1004::init()
{
    uint16_t value = getConfigRegister();
    printf("CONFIG REGISTER YY: " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(value));

    reset();

    value = getConfigRegister();
    
    while ((value & 0x8000) != 0)
    {

        // wait_us(3000*1000);
    }

    setRepeatedMeasurements(true);

    printf("After reset, only repeated " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(value));

    // this->enableMeasurement(FDC1004::Channel::CIN1); // Messungen aktivieren

    setMeasurementRate(FDC1004::MeasurementRate::Rate100);

    // fdc1004.setMeasurementOffsetCapacitance(FDC1004::Register::ConfigMeasurementReg1, 31);//Einstellbar von 0 bis 31, 0 => kein Offset, 31 => 96,875pF Offset

    uint16_t testausgabe_config1 = getConfigRegister();
    printf("Configurationsregister :  " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(testausgabe_config1));

    bool status=setConfigurationRegister();
    if(status)
        printf("Configuration Registers have been configured\n");

    getMeasure1();
    getMeasure2();
    getMeasure3();
    getMeasure4();
    
}


bool FDC1004::setConfigurationRegister()
{
    bool success1,success2,success3,success4;
    success1=setMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg1, FDC1004::Channel::CIN1, FDC1004::Channel::DISABLED, 1);
    success2=setMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg2, FDC1004::Channel::CIN2, FDC1004::Channel::DISABLED);
    success3=setMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg3, FDC1004::Channel::CIN3, FDC1004::Channel::DISABLED);
    success4=setMeasurementChannelConfig(FDC1004::Register::ConfigMeasurementReg4, FDC1004::Channel::CIN4, FDC1004::Channel::DISABLED);
    if(success1 && success2 && success3 && success4)
        return true;
    else
        return false;
}

bool FDC1004::setMeasurementChannelConfig(FDC1004::Register measureConfigReg, FDC1004::Channel channelA, FDC1004::Channel channelB, uint8_t capdacValue)
{
    // uint16_t value = get_register((char)measureConfigReg);
    uint16_t value = 0x00;
    value |= ((uint16_t)channelA << 13);
    value |= ((uint16_t)channelB << 10);

    bool success = true;

    if (channelB == FDC1004::Channel::CAPDAC)
    {

        if (capdacValue > 31)
        {

            // printf("Offset im falschen Bereich, maximal 31");
            return false;
        }
        value |= (capdacValue << 5);
    }

    writeRegister(measureConfigReg, value);
    return success;
}

void FDC1004::setMeasurementRate(FDC1004::MeasurementRate rate)
{

    uint16_t value = getConfigRegister();

    value &= ~(0x03 << 10);
    value |= ((uint8_t)rate) << 10;

    if (rate == FDC1004::MeasurementRate::Rate100)
    {
        setConfigRegisterBit(value, 11, 0);
        setConfigRegisterBit(value, 10, 1);
    }
    else if (rate == FDC1004::MeasurementRate::Rate200)
    {
        setConfigRegisterBit(value, 11, 1);
        setConfigRegisterBit(value, 10, 0);
    }
    else if (rate == FDC1004::MeasurementRate::Rate400)
    {

        setConfigRegisterBit(value, 11, 1);
        setConfigRegisterBit(value, 10, 1);
    }

    writeRegister(Register::ConfigRegister, value);
}

void FDC1004::writeRegister(FDC1004::Register reg, uint16_t& reg_value)
{

    char data[3];
    data[0] = (uint8_t)reg;
    data[1] = (char)(reg_value >> 8);
    data[2] = (char)reg_value;

    int rc = _i2c.write(address, &data[0], 3);
    if (rc != 0)
    {
        printf("Fehler i2c write");
    }
    
}

bool FDC1004::enableMeasurement(FDC1004::Channel CIN)
{
    uint16_t value = getConfigRegister();
    switch (CIN)
    {
    case Channel::CIN1:
        setConfigRegisterBit(value, 7, 1);
        return 1;
    case Channel::CIN2:
        setConfigRegisterBit(value, 6, 1);
        return 1;
    case Channel::CIN3:
        setConfigRegisterBit(value, 5, 1);
        return 1;
    case Channel::CIN4:
        setConfigRegisterBit(value, 4, 1);
        return 1;
    default:
        printf("invalid measurement value");
    }
    return 0;
}

bool FDC1004::isMeasurementEnabled(FDC1004::Channel CIN)
{
    uint16_t value= getConfigRegister();
    switch(CIN) {
    case Channel::CIN1:
        if(value & 1<<7)
            return 1;
        else 
            return 0;
    case Channel::CIN2:
        if(value & 1<<6)
            return 1;
        else 
            return 0;
    case Channel::CIN3:
        if(value & 1<<5)
            return 1;
        else 
            return 0;
    case Channel::CIN4:
        if(value & 1<<4)
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
    uint16_t value= getConfigRegister();
    switch(CIN) {
    case Channel::CIN1:
        if(value & 1<<3)
            return 1;
        else 
            return 0;
    case Channel::CIN2:
        if(value & 1<<2)
            return 1;
        else 
            return 0;
    case Channel::CIN3:
        if(value & 1<<1)
            return 1;
        else 
            return 0;
    case Channel::CIN4:
        if(value & 1<<0)
            return 1;
        else 
            return 0;
    default:
        printf("invalid measurement value");
    }
    return 0;
}

void FDC1004::disableMeasurement(FDC1004::Channel CIN)
{
    uint16_t value = getConfigRegister();
    switch (CIN)
    {
    case Channel::CIN1:
        setConfigRegisterBit(value, 7, 0);
        break;
    case Channel::CIN2:
        setConfigRegisterBit(value, 6, 0);
        break;
    case Channel::CIN3:
        setConfigRegisterBit(value, 5, 0);
        break;
    case Channel::CIN4:
        setConfigRegisterBit(value, 4, 0);
        break;
    default:
        printf("invalid measurement value");
    }
}

void FDC1004::measure()
{
    uint32_t measure1, measure2, measure3, measure4;
    static int count = 0;
    measure1 = getMeasure1();
    measure2 = getMeasure2();
    measure3 = getMeasure3();
    measure4 = getMeasure4();

    printf("Measure1: %fpF\r\n", (measure1 / pow(2, 19)));
    printf("Measure2: %fpF\r\n", (measure2 / pow(2, 19)));
    printf("Measure3: %fpF\r\n", (measure3 / pow(2, 19)));
    printf("Measure4: %fpF\r\n", (measure4 / pow(2, 19)));

    printf("Reading Number: %d\r\n\r\n", count += 1);

    wait_us(4000 * 1000);
}

void FDC1004::activateDifferentialMeasurements1(uint16_t &value)
{

    setConfMeas1Bit(value, 15, 0);
    setConfMeas1Bit(value, 14, 0);
    setConfMeas1Bit(value, 13, 0);

    setConfMeas1Bit(value, 12, 1);
    setConfMeas1Bit(value, 11, 1);
    setConfMeas1Bit(value, 10, 1);
}

void FDC1004::activateDifferentialMeasurements2(uint16_t &value)
{

    setConfMeas2Bit(value, 15, 0);
    setConfMeas2Bit(value, 14, 0);
    setConfMeas2Bit(value, 13, 1);

    setConfMeas2Bit(value, 12, 1);
    setConfMeas2Bit(value, 11, 1);
    setConfMeas2Bit(value, 10, 1);
}

void FDC1004::activateDifferentialMeasurements3(uint16_t &value)
{

    setConfMeas3Bit(value, 15, 0);
    setConfMeas3Bit(value, 14, 1);
    setConfMeas3Bit(value, 13, 0);

    setConfMeas3Bit(value, 12, 1);
    setConfMeas3Bit(value, 11, 1);
    setConfMeas3Bit(value, 10, 1);
}

void FDC1004::activateDifferentialMeasurements4(uint16_t &value)
{

    setConfMeas4Bit(value, 15, 0);
    setConfMeas4Bit(value, 14, 0);
    setConfMeas4Bit(value, 13, 0);

    setConfMeas4Bit(value, 12, 1);
    setConfMeas4Bit(value, 11, 1);
    setConfMeas4Bit(value, 10, 1);
}

void FDC1004::setConfMeas1Bit(uint16_t &value, u_int8_t position, uint8_t bit)
{

    setRegisterBit(value, position, bit, 0x08);
}

void FDC1004::setConfMeas2Bit(uint16_t &value, u_int8_t position, uint8_t bit)
{

    setRegisterBit(value, position, bit, 0x09);
}

void FDC1004::setConfMeas3Bit(uint16_t &value, u_int8_t position, uint8_t bit)
{

    setRegisterBit(value, position, bit, 0x0A);
}

void FDC1004::setConfMeas4Bit(uint16_t &value, u_int8_t position, uint8_t bit)
{

    setRegisterBit(value, position, bit, 0x0B);
}

void FDC1004::setConfigRegisterBit(uint16_t &value, u_int8_t position, uint8_t bit)
{

    setRegisterBit(value, position, bit, 0x0C);
}

void FDC1004::setRegisterBit(uint16_t &value, u_int8_t position, uint8_t bit, char registeraddress)
{

    // uint8_t FDC1004Address = 0b1010000 << 1;

    if (bit == 1)
    {
        value = value | (1 << position);
    }
    else if (bit == 0)
    {
        value = value & ~(1 << position);
    }
    else
    {
        printf("Ungültige Eingabe, Bit nur auf 0/1 setzen");
    }
    char data[3];
    data[0] = registeraddress; // ConfigurationReg;
    data[1] = (char)(value >> 8);
    data[2] = (char)value;

    int rc = _i2c.write(FDC1004Address, &data[0], 3);
    if (rc != 0)
    {
        printf("Fehler i2c write");
    }
}

bool FDC1004::setGainCalibration(float gain,FDC1004::Register reg )
{
    if(gain>= 4 || gain < 0)
        return 0;
    uint16_t value=0;
    value = gain*(pow(2,14));
    writeRegister(reg, value);
    return true;
}

float FDC1004::getGainCalibration(FDC1004::Register reg)
{
    float gain=0;
    gain = (readRegister((char)reg) / pow(2,14));
    return gain;
    
}

bool FDC1004::setOffsetCalibration(float offset,FDC1004::Register reg )
{
    if(offset>= 16 || offset <= -16)
        return 0;
    offset=(0.5*offset)+8;
    uint16_t value=0;
    value=offset*(pow(2,11));
    writeRegister(reg, value);
    return true;
}

float FDC1004::getOffsetCalibration(FDC1004::Register reg)
{
    float offset=0;
    offset = (readRegister((char)reg) / pow(2,11) - 8) *2;
    return offset; 
}


