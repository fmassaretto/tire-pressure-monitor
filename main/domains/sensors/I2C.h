#pragma once
#ifndef _PRESSURE_H
#define _PRESSURE_H

#include <mutex>
#include "cbspI2C.h"
#include "stdio.h"

class I2C
{
private:
    static I2C *pinstance_;
    static std::mutex mutex_;
    static cbspI2C I2CChannel1;

protected:
    I2C();
    ~I2C() {};

public:
    I2C(I2C &other) = delete;
    void operator=(const I2C &) = delete;
    static I2C *GetInstance();
    static void init();
    cbspI2C &getI2CChannel1();
};

#endif