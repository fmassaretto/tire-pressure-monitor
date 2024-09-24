#pragma once
#ifndef _TEMPERATURE_H
#define _TEMPERATURE_H

#include "./domains/sensors/I2C.h"
#include "cBMP280.h"

class Temperature
{
private:
    cBMP280 BMP280;
    I2C *i2c;

public:
    Temperature();
    void init();
    float getTemperature();
};

#endif
