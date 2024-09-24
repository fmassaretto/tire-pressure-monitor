#include "Temperature.h"

Temperature::Temperature()
{
    I2C::GetInstance();
}

void Temperature::init()
{
    BMP280.init(i2c->getI2CChannel1());
}

float Temperature::getTemperature()
{
    BMP280.poll();

    return BMP280.getTemperature();
}
