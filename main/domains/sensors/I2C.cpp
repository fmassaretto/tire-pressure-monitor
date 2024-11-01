#include "I2C.h"

I2C *I2C::pinstance_{nullptr};
std::mutex I2C::mutex_;
cbspI2C I2C::I2CChannel1;

I2C::I2C()
{
    printf("I2C contructor");
    I2C::init(); // Exemplo que deu certo inicializar objeto no construtor sem dar crash no ESP
}

void I2C::init()
{
    printf("I2C.cpp: init()\n");
    I2CChannel1.init(I2C_NUM_1, GPIO_NUM_33, GPIO_NUM_32);
    I2CChannel1.openAsMaster(100000);
}

I2C *I2C::GetInstance()
{
    printf("I2C.cpp: getInstance()\n");
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr)
    {
        pinstance_ = new I2C();
    }
    return pinstance_;
}

cbspI2C &I2C::getI2CChannel1()
{
    return I2CChannel1;
}