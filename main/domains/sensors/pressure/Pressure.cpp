#include "Pressure.h"

Pressure::Pressure()
{
    I2C::GetInstance();
}

void Pressure::init()
{
    SMP3011.init(i2c->getI2CChannel1());
}

float Pressure::getPressureInKPa()
{
    SMP3011.poll();
    // printf("Pressure.cpp: %6.2f", SMP3011.getPressure());
    return SMP3011.getPressure();
}

float Pressure::getPressureInPsi()
{
    return this->getPressureInKPa() * 0.14503773773020923;
}

float Pressure::getPressureInBar()
{
    return this->getPressureInKPa() / 100;
}

float Pressure::getPressure(bool changeScale)
{
    if (changeScale)
    {
        printf("BAR\n");
        return this->getPressureInBar();
    }
    else
    {
        printf("PSI\n");
        return this->getPressureInPsi();
    }
}

float Pressure::getRecomendedPressure(bool changeScale)
{
    if (changeScale)
    {
        return 1.0;
    }
    else
    {
        return 2.0;
    }
}

float Pressure::getTemperature()
{
    return SMP3011.getTemperature();
}