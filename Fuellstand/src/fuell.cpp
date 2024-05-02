#include "fuell.hpp"

#define FDC1004Address 0b1010000 << 1

#define FDC1004_ADRESS 0b1010000 << 1
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

uint16_t FDC1004::get_MEAS1_MSB()
{
    return readRegister(0x00);
}
uint16_t FDC1004::get_MEAS1_LSB()
{
    return readRegister(0x01);
}
uint16_t FDC1004::get_MEAS2_MSB()
{
    return readRegister(0x02);
}
uint16_t FDC1004::get_MEAS2_LSB()
{
    return readRegister(0x03);
}
uint16_t FDC1004::get_MEAS3_MSB()
{
    return readRegister(0x04);
}
uint16_t FDC1004::get_MEAS3_LSB()
{
    return readRegister(0x05);
}
uint16_t FDC1004::get_MEAS4_MSB()
{
    return readRegister(0x06);
}
uint16_t FDC1004::get_MEAS4_LSB()
{
    return readRegister(0x07);
}
uint16_t FDC1004::get_CONF_MEAS1()
{
    return readRegister(0x08);
}
uint16_t FDC1004::get_CONF_MEAS2()
{
    return readRegister(0x09);
}
uint16_t FDC1004::get_CONF_MEAS3()
{
    return readRegister(0x0A);
}
uint16_t FDC1004::get_CONF_MEAS4()
{
    return readRegister(0x0B);
}
uint16_t FDC1004::get_config_register()
{
    return readRegister(0x0C);
}
uint16_t FDC1004::get_OFFSET_CAL_CIN1()
{
    return readRegister(0x0D);
}
uint16_t FDC1004::get_OFFSET_CAL_CIN2()
{
    return readRegister(0x0E);
}
uint16_t FDC1004::get_OFFSET_CAL_CIN3()
{
    return readRegister(0x0F);
}
uint16_t FDC1004::get_OFFSET_CAL_CIN4()
{
    return readRegister(0x10);
}
uint16_t FDC1004::get_GAIN_CAL_CIN1()
{
    return readRegister(0x11);
}
uint16_t FDC1004::get_GAIN_CAL_CIN2()
{
    return readRegister(0x12);
}
uint16_t FDC1004::get_GAIN_CAL_CIN3()
{
    return readRegister(0x13);
}
uint16_t FDC1004::get_GAIN_CAL_CIN4()
{
    return readRegister(0x14);
}
uint16_t FDC1004::get_MANUFACTURER_ID()
{
    return readRegister(0xFE);
}
uint16_t FDC1004::get_DEVICE_ID()
{
    return readRegister(0xFF);
}

// bool FDC1004::readRegister(Register reg, uint16_t &value)
// {
// }

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

uint16_t FDC1004::getManufacturerId()
{
    return readRegister(0xFE);
}

// bool FDC1004::readValue(Channel channel, float& value)
// {

// }

// bool FDC1004::readRawValue(Channel channel, uint32_t& value)
// {

// }

uint32_t FDC1004::getMeasure1()
{

    uint16_t meas1_1 = get_MEAS1_MSB();
    uint16_t meas1_2 = get_MEAS1_LSB();
    uint32_t complete_measure_binary1 = meas1_2 >> 8;
    complete_measure_binary1 += meas1_1 << 8;
    return complete_measure_binary1;
}

uint32_t FDC1004::getMeasure2()
{

    uint16_t meas2_1 = get_MEAS2_MSB();
    uint16_t meas2_2 = get_MEAS2_LSB();
    uint32_t complete_measure_binary2 = meas2_2 >> 8;
    complete_measure_binary2 += meas2_1 << 8;
    return complete_measure_binary2;
}
uint32_t FDC1004::getMeasure3()
{

    uint16_t meas3_1 = get_MEAS3_MSB();
    uint16_t meas3_2 = get_MEAS3_LSB();
    uint32_t complete_measure_binary3 = meas3_2 >> 8;
    complete_measure_binary3 += meas3_1 << 8;
    return complete_measure_binary3;
}
uint32_t FDC1004::getMeasure4()
{

    uint16_t meas4_1 = get_MEAS4_MSB();
    uint16_t meas4_2 = get_MEAS4_LSB();
    uint32_t complete_measure_binary4 = meas4_2 >> 8;
    complete_measure_binary4 += meas4_1 << 8;
    return complete_measure_binary4;
}

void FDC1004::reset()
{

    uint16_t value = 0;
    set_config_register_bit(value, 15, 1);
}

void FDC1004::set_repeated_measurements(bool set)
{
    // readRegister
    uint16_t value = 0;
    if (set) 
    {
        set_config_register_bit(value, 8, 1);
    }
    else
    {
        set_config_register_bit(value, 8, 0);
    }
    // writeRegister(ConfigRegister, value);
}

void FDC1004::init()
{
    //    FDC1004 fdc1004(i2c);

    uint16_t value = this->get_config_register();
    printf("CONFIG REGISTER YY: " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(value));

    this->reset();

    value = this->get_config_register();

    while ((value & 0x8000) != 0)
    {

        // wait_us(3000*1000);
    }
    // value = this->.get_config_register();

    // this->reset();

    this->set_repeated_measurements(true);

    printf("After reset, only repeated " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(value));

    // this->enableMeasurement(FDC1004::Channel::CIN1); // Messungen aktivieren

    this->setMeasurementRate(FDC1004::MeasurementRate::Rate100);

    // fdc1004.set_measurement_offset_capacitance(FDC1004::Register::ConfigMeasurementReg1, 31);//Einstellbar von 0 bis 31, 0 => kein Offset, 31 => 96,875pF Offset

    uint16_t testausgabe_config1 = this->get_config_register();
    printf("Configurationsregister :  " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(testausgabe_config1));

    // fdc1004.set_measurement_channel_config(FDC1004::Register::ConfigMeasurementReg1, FDC1004::Channel::CIN1, FDC1004::Channel::CAPDAC, 31);
    // uint measureChannel1 = fdc1004.get_measurement_channel_config(FDC1004::Register::ConfigMeasurementReg1);

    testausgabe_config1 = this->get_CONF_MEAS1();
    printf("Configurationsregister zur Messung 1: " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(testausgabe_config1));

    this->set_measurement_channel_config(FDC1004::Register::ConfigMeasurementReg1, FDC1004::Channel::CIN1, FDC1004::Channel::DISABLED, 1);
    this->set_measurement_channel_config(FDC1004::Register::ConfigMeasurementReg2, FDC1004::Channel::CIN2, FDC1004::Channel::DISABLED);
    this->set_measurement_channel_config(FDC1004::Register::ConfigMeasurementReg3, FDC1004::Channel::CIN3, FDC1004::Channel::DISABLED);
    this->set_measurement_channel_config(FDC1004::Register::ConfigMeasurementReg4, FDC1004::Channel::CIN4, FDC1004::Channel::DISABLED);

    // uint16_t configreg4 = fdc1004.get_register((char)FDC1004::Register::ConfigMeasurementReg4);
    // printf("Measurement 4 config register before"BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(configreg4));
    // fdc1004.set_measurement_channel_config(FDC1004::Register::ConfigMeasurementReg4, FDC1004::Channel::CIN4, FDC1004::Channel::CAPDAC, 31);
    // configreg4 = fdc1004.get_register((char)FDC1004::Register::ConfigMeasurementReg4);
    // printf("Measurement 4 config register after"BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(configreg4));

    // fdc1004.setMeasurementRate(FDC1004::MeasurementRate::Rate100);

    // printf("config register: %04X\r\n", value);
    value = this->get_config_register();
    printf("EWARTET; CONFIG REGISTER 4 5 6 7 gesetzt: " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(value));

    // value = 0;
    // fdc1004.activate_differential_measurements_1(value);
    printf("Config 1 Measurement register  " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(value));

    // value = fdc1004.get_config_register();

    // printf("CONFIG REGISTER AFTER RESET: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(value));
    // value = 0;
    // value = fdc1004.get_config_register();

    // printf("NOCHMAL CONFIG REGISTER AFTER RESET; DAVOR NOCH GETCONFIG: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(value));

    // offset1 = fdc1004.get_CONF_MEAS1();
    // printf("CONF_MEAS1:  "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(offset1));

    printf("config register vor while:  " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(value));
}

/*
bool FDC1004::set_measurement_offset_capacitance(FDC1004::Register measureConfigReg, uint8_t offset){

    uint16_t value = get_register((char)measureConfigReg);
    if(offset > 31 || offset < 0){
        //printf("Offset im falschen Bereich, maximal 31");
        return false;
    }

    //uint16_t capdac = 0;
    value |= (offset << 5);
    write_register(measureConfigReg, value);
    return true;

}

*/

bool FDC1004::set_measurement_channel_config(FDC1004::Register measureConfigReg, FDC1004::Channel channelA, FDC1004::Channel channelB, uint8_t capdacValue)
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

    write_register(measureConfigReg, value);
    return success;
}

void FDC1004::setMeasurementRate(FDC1004::MeasurementRate rate)
{

    uint16_t value = get_config_register();

    value &= ~(0x03 << 10);
    value |= ((uint8_t)rate) << 10;

    if (rate == FDC1004::MeasurementRate::Rate100)
    {
        set_config_register_bit(value, 11, 0);
        set_config_register_bit(value, 10, 1);
    }
    else if (rate == FDC1004::MeasurementRate::Rate200)
    {
        set_config_register_bit(value, 11, 1);
        set_config_register_bit(value, 10, 0);
    }
    else if (rate == FDC1004::MeasurementRate::Rate400)
    {

        set_config_register_bit(value, 11, 1);
        set_config_register_bit(value, 10, 1);
    }

    write_register(Register::ConfigRegister, value);
}

void FDC1004::write_register(FDC1004::Register reg, uint16_t &reg_value)
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
/*
void FDC1004::measurementRate(uint16_t& value, uint16_t rate){

    if(rate == 100){
        set_config_register_bit(value, 11, 0);
        set_config_register_bit(value, 10, 1);
    } else if(rate == 200){
        set_config_register_bit(value, 11, 1);
        set_config_register_bit(value, 10, 0);
    } else if(rate == 400){

        set_config_register_bit(value, 11, 1);
        set_config_register_bit(value, 10, 1);
    }
}
*/
bool FDC1004::enableMeasurement(FDC1004::Channel CIN)
{
    uint16_t value = get_config_register();
    switch (CIN)
    {
    case Channel::CIN1:
        set_config_register_bit(value, 7, 1);
        return 1;
    case Channel::CIN2:
        set_config_register_bit(value, 6, 1);
        return 1;
    case Channel::CIN3:
        set_config_register_bit(value, 5, 1);
        return 1;
    case Channel::CIN4:
        set_config_register_bit(value, 4, 1);
        return 1;
    default:
        printf("invalid measurement value");
    }
    return 0;
}

bool FDC1004::isMeasurementEnabled(FDC1004::Channel CIN)
{
    uint16_t value= get_config_register();
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

// void FDC1004::disableMeasurement(FDC1004::Channel CIN)
// {
//     uint16_t value = get_config_register();
//     switch (CIN)
//     {
//     case Channel::CIN1:
//         set_config_register_bit(value, 7, 0);
//         break;
//     case Channel::CIN2:
//         set_config_register_bit(value, 6, 0);
//         break;
//     case Channel::CIN3:
//         set_config_register_bit(value, 5, 0);
//         break;
//     case Channel::CIN4:
//         set_config_register_bit(value, 4, 0);
//         break;
//     default:
//         printf("invalid measurement value");
//     }
// }

void FDC1004::measure()
{
    uint32_t measure1, measure2, measure3, measure4;
    static int count = 0;
    measure1 = this->getMeasure1();
    measure2 = this->getMeasure2();
    measure3 = this->getMeasure3();
    measure4 = this->getMeasure4();

    printf("Measure1: %fpF\r\n", (measure1 / pow(2, 19)));
    printf("Measure2: %fpF\r\n", (measure2 / pow(2, 19)));
    printf("Measure3: %fpF\r\n", (measure3 / pow(2, 19)));
    printf("Measure4: %fpF\r\n", (measure4 / pow(2, 19)));

    printf("Reading Number: %d\r\n\r\n", count += 1);

    wait_us(4000 * 1000);
}

// void FDC1004::enable_measurement_2(){
//     uint16_t value = get_config_register();
//     set_config_register_bit(value, 6, 1);
// }

// void FDC1004::enable_measurement_3(){
//     uint16_t value = get_config_register();
//     set_config_register_bit(value, 5, 1);
// }

// void FDC1004::enable_measurement_4(){
//     uint16_t value = get_config_register();
//     set_config_register_bit(value, 4, 1);
// }

void FDC1004::disable_measurement_1()
{
    uint16_t value = get_config_register();
    set_config_register_bit(value, 7, 0);
}

void FDC1004::disable_measurement_2()
{
    uint16_t value = get_config_register();
    set_config_register_bit(value, 6, 0);
}

void FDC1004::disable_measurement_3()
{
    uint16_t value = get_config_register();
    set_config_register_bit(value, 5, 0);
}

void FDC1004::disable_measurement_4()
{
    uint16_t value = get_config_register();
    set_config_register_bit(value, 4, 0);
}

void FDC1004::activate_differential_measurements_1(uint16_t &value)
{

    set_conf_meas1_bit(value, 15, 0);
    set_conf_meas1_bit(value, 14, 0);
    set_conf_meas1_bit(value, 13, 0);

    set_conf_meas1_bit(value, 12, 1);
    set_conf_meas1_bit(value, 11, 1);
    set_conf_meas1_bit(value, 10, 1);
}

void FDC1004::activate_differential_measurements_2(uint16_t &value)
{

    set_conf_meas2_bit(value, 15, 0);
    set_conf_meas2_bit(value, 14, 0);
    set_conf_meas2_bit(value, 13, 1);

    set_conf_meas2_bit(value, 12, 1);
    set_conf_meas2_bit(value, 11, 1);
    set_conf_meas2_bit(value, 10, 1);
}

void FDC1004::activate_differential_measurements_3(uint16_t &value)
{

    set_conf_meas3_bit(value, 15, 0);
    set_conf_meas3_bit(value, 14, 1);
    set_conf_meas3_bit(value, 13, 0);

    set_conf_meas3_bit(value, 12, 1);
    set_conf_meas3_bit(value, 11, 1);
    set_conf_meas3_bit(value, 10, 1);
}

void FDC1004::activate_differential_measurements_4(uint16_t &value)
{

    set_conf_meas4_bit(value, 15, 0);
    set_conf_meas4_bit(value, 14, 0);
    set_conf_meas4_bit(value, 13, 0);

    set_conf_meas4_bit(value, 12, 1);
    set_conf_meas4_bit(value, 11, 1);
    set_conf_meas4_bit(value, 10, 1);
}

void FDC1004::set_conf_meas1_bit(uint16_t &value, u_int8_t position, uint8_t bit)
{

    set_register_bit(value, position, bit, 0x08);
}

void FDC1004::set_conf_meas2_bit(uint16_t &value, u_int8_t position, uint8_t bit)
{

    set_register_bit(value, position, bit, 0x09);
}

void FDC1004::set_conf_meas3_bit(uint16_t &value, u_int8_t position, uint8_t bit)
{

    set_register_bit(value, position, bit, 0x0A);
}

void FDC1004::set_conf_meas4_bit(uint16_t &value, u_int8_t position, uint8_t bit)
{

    set_register_bit(value, position, bit, 0x0B);
}

void FDC1004::set_config_register_bit(uint16_t &value, u_int8_t position, uint8_t bit)
{

    set_register_bit(value, position, bit, 0x0C);
}

void FDC1004::set_register_bit(uint16_t &value, u_int8_t position, uint8_t bit, char registeraddress)
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
