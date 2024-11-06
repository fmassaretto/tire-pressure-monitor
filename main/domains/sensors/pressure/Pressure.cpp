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
        return this->getPressureInBar();
    }
    else
    {
        return this->getPressureInPsi();
    }
}

float Pressure::getRecomendedPressure(bool changeScale)
{
    float p1 = changeScale ? getPressureInBar() : getPressureInPsi();
    float const t1 = 25.0;
    float t2 = getTemperature();

    return p1 * (t2 / t1);
}

float Pressure::getTemperature()
{
    return SMP3011.getTemperature();
}