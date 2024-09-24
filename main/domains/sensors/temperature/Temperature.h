#pragma once
#ifndef _TEMPERATURE_H
#define _TEMPERATURE_H

#include "cbspI2C.h"
#include "cBMP280.h"

class Temperature
{
private:
    cbspI2C I2CChannel1;
    cBMP280 BMP280;

public:
    Temperature();
    void init();
    float getTemperature();
};

#endif
