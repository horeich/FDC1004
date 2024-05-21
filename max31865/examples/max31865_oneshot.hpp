/**
 * @file    max31865_oneshot.hpp
 * @author  Andreas Reichle (HOREICH UG) <andreas.reichle@horeich.de>
 */

#ifndef MAX31865_ONESHOT_HPP
#define MAX31865_ONESHOT_HPP

#include "../src/max31865.hpp"
#include "mbed.h"
#include "rtos.h"

class MAX31865_Oneshot
{
public:
    MAX31865_Oneshot() = default;
    ~MAX31865_Oneshot() = default;

    static void Run();

private:  
    static void Ready();

private:
    static rtos::EventFlags Rdy_flag;
    static mbed::DigitalOut Led;
};

#endif // MAX31865_ONESHOT_HPP