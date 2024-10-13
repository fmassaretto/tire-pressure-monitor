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
