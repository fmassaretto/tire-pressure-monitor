#include "Temperature.h"

cbspI2C I2CChannel1;
cBMP280 BMP280;

Temperature::Temperature()
{
}

void Temperature::init()
{
    I2CChannel1.init(I2C_NUM_1, GPIO_NUM_33, GPIO_NUM_32);
    I2CChannel1.openAsMaster(100000);
    BMP280.init(I2CChannel1);
}

float Temperature::getTemperature()
{
    BMP280.poll();

    return BMP280.getTemperature();
}
