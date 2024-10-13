#pragma once
#ifndef PRESSURE_H
#define PRESSURE_H

#include "domains/sensors/I2C.h"
#include "cSMP3011.h"

class Pressure
{
private:
    cSMP3011 SMP3011;
    I2C *i2c;
    float getPressureInKPa();

public:
    Pressure();
    void init();
    float getPressureInPsi();
    float getPressureInBar();
};

#endif
