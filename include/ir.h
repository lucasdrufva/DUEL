#pragma once
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "game.h"
#include <Arduino.h>

class IR
{
public:
    void begin();
    void shoot();

private:
    uint16_t sAddress = 0x0102;
    uint16_t sCommand;
    uint64_t nec;
};