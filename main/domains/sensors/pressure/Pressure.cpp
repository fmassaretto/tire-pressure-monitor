#include "Pressure.h"

Pressure::Pressure()
{
    printf("Pressure.cpp: Pressure()\n");
    I2C::GetInstance();
}

void Pressure::init()
{
    printf("Pressure.cpp: init()\n");
    SMP3011.init(i2c->getI2CChannel1());
}

float Pressure::getPressureInKPa()
{
    SMP3011.poll();
    printf("Pressure.cpp: %6.2f", SMP3011.getPressure());
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
